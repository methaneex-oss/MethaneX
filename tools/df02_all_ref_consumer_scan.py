#!/usr/bin/env python3
"""Read-only all-ref donor path and reverse-consumer discovery for JARVIS DF-02.

This tool produces evidence for Builder semantic review. Symbol/path matches are
candidate consumers, never automatic semantic-successor or acceptance decisions.
"""
from __future__ import annotations
import argparse, collections, csv, hashlib, json, pathlib, re, subprocess, sys
from typing import Dict, List, Tuple

AUDIT_TOOL_PATHS = {
    "tools/df02_all_ref_consumer_scan.py",
    "tools/df02_all_ref_audit_inputs.json",
    ".github/workflows/df02-all-ref-consumer-scan.yml",
}
TEXT_EXTS = {".c",".cc",".cpp",".cxx",".h",".hh",".hpp",".hxx",".m",".mm",".ts",".tsx",".js",".jsx",".py",".md",".yml",".yaml",".json",".toml",".cmake",".sh",".ps1",".txt",".xml",".sql",".proto",".ini",".cfg",".rst",".html",".css",".gradle",".properties"}
STOP = {"main","test","tests","run","get","set","create","update","delete","find","read","write","open","close","init","reset","clear","process","execute","handle","on","off","to","from","value","data","id","name","type","status","state","action","memory","brain","runtime","event","context","result","error","config","manager","controller","engine","system","model","base","current","new","old","testcase","suite","string","vector","map","optional","shared_ptr","unique_ptr","size","count","index","begin","end","empty","push_back","emplace"}

def git(args: List[str], binary: bool=False) -> bytes | str:
    p = subprocess.run(["git", *args], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
    if p.returncode:
        raise RuntimeError(f"git {' '.join(args)} failed ({p.returncode}): {p.stderr.decode(errors='replace')[-3000:]}")
    return p.stdout if binary else p.stdout.decode("utf-8", errors="replace")

def parse_tree(ref: str) -> Dict[str,str]:
    raw = git(["ls-tree","-r","-z","--full-tree",ref], binary=True)
    out = {}
    for rec in raw.split(b"\0"):
        if not rec: continue
        meta, path_b = rec.split(b"\t",1)
        mode, typ, sha = meta.decode("ascii").split()
        if typ == "blob": out[path_b.decode("utf-8",errors="surrogateescape")] = sha
    return out

def cat_file_batch(shas: List[str]) -> Dict[str,bytes]:
    if not shas: return {}
    p = subprocess.Popen(["git","cat-file","--batch"],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    raw, err = p.communicate(("\n".join(shas)+"\n").encode())
    if p.returncode: raise RuntimeError(f"git cat-file --batch failed: {err.decode(errors='replace')[-2000:]}")
    out, pos = {}, 0
    for expected in shas:
        nl = raw.find(b"\n",pos)
        if nl < 0: raise RuntimeError("truncated cat-file batch header")
        header = raw[pos:nl].split()
        pos = nl+1
        if len(header)<3 or header[1]!=b"blob": raise RuntimeError(f"missing/non-blob object: {expected} / {header!r}")
        size = int(header[2]); data = raw[pos:pos+size]
        if len(data)!=size: raise RuntimeError(f"truncated blob: {expected}")
        pos += size
        if pos<len(raw) and raw[pos:pos+1]==b"\n": pos += 1
        out[expected] = data
    return out

def is_text_path(path: str) -> bool:
    name = pathlib.PurePosixPath(path).name
    return name in {"CMakeLists.txt","Makefile","Dockerfile",".gitignore",".editorconfig"} or pathlib.PurePosixPath(path).suffix.lower() in TEXT_EXTS

def category(path: str) -> str:
    p=path.lower()
    if p.startswith("docs/") or p.endswith((".md",".rst")): return "documentation"
    if ".github/workflows/" in p or p.endswith((".yml",".yaml")): return "workflow"
    if "/tests/" in p or p.startswith("tests/") or "_suite." in p or "test_" in pathlib.PurePosixPath(p).name: return "test"
    if pathlib.PurePosixPath(p).name=="cmakelists.txt" or p.endswith(".cmake") or pathlib.PurePosixPath(p).name=="makefile": return "build"
    if "/src/" in p or "/include/" in p or p.startswith(("interfaces/","core/")): return "source"
    return "other"

def extract_symbols(content: str, path: str) -> set[str]:
    found=set()
    patterns=[
      r"\b(?:class|struct|enum(?:\s+class)?|namespace|using|typedef)\s+([A-Za-z_]\w*)",
      r"\b[A-Za-z_]\w*::([A-Za-z_]\w*)\s*\(",
      r"\b(?:export\s+)?(?:class|interface|type|enum|function|const|let|var)\s+([A-Za-z_]\w*)",
      r"^\s*(?:def|class)\s+([A-Za-z_]\w*)",
      r"^\s*(?:[\w:<>,*&]+\s+)+([A-Za-z_]\w*)\s*\([^;{}]*\)\s*(?:const\s*)?(?:noexcept\s*)?(?:override\s*)?(?:\{|;)",
      r"\b(?:add_executable|add_library|add_test|add_custom_target|add_subdirectory)\s*\(\s*([A-Za-z_][A-Za-z0-9_.-]*)",
    ]
    for pat in patterns:
        for m in re.finditer(pat,content,re.MULTILINE):
            name=m.group(1)
            if len(name)>=6 and name.lower() not in STOP: found.add(name)
    for inc in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]',content,re.MULTILINE):
        stem=pathlib.PurePosixPath(inc).stem
        if len(stem)>=7: found.add(stem)
    stem=pathlib.PurePosixPath(path).stem
    if len(stem)>=8 and stem.lower() not in STOP: found.add(stem)
    return found

def self_test():
    sample="class DevelopmentalLearning {};\\nstruct ExperienceMemory {};\\nvoid updatePredictionContext(int x);\\n"
    syms=extract_symbols(sample,"core/cpp/src/developmental_learning.cpp")
    assert {"DevelopmentalLearning","ExperienceMemory","updatePredictionContext"} <= syms
    assert category("core/cpp/tests/example_suite.cpp")=="test"
    assert category(".github/workflows/brain-ci.yml")=="workflow"
    assert category("core/cpp/src/brain.cpp")=="source"
    print("DF-02 scanner self-test: PASS")

def write_csv(path, headers, rows):
    with path.open("w",newline="",encoding="utf-8") as f:
        w=csv.DictWriter(f,fieldnames=headers); w.writeheader()
        for row in rows: w.writerow(row)

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--self-test",action="store_true")
    ap.add_argument("--inputs",default="tools/df02_all_ref_audit_inputs.json")
    ap.add_argument("--output",default="artifacts/df02")
    args=ap.parse_args()
    if args.self_test: self_test(); return 0

    inputs=json.loads(pathlib.Path(args.inputs).read_text(encoding="utf-8"))
    donor_sha=inputs["donor_sha"]; candidate_sha=inputs["candidate_sha"]
    donor_paths=sorted(set(inputs["donor_paths"]))
    if len(donor_paths)!=159: raise RuntimeError(f"expected 159 donor paths, got {len(donor_paths)}")
    git(["cat-file","-e",donor_sha+"^{commit}"]); git(["cat-file","-e",candidate_sha+"^{commit}"])

    refs_raw=git(["for-each-ref","--format=%(refname:short)%09%(objectname)","refs/remotes/origin"])
    branch_groups=collections.defaultdict(list)
    for line in refs_raw.splitlines():
        if "\t" not in line: continue
        name,sha=line.split("\t",1)
        if name.endswith("/HEAD") or name=="origin/HEAD": continue
        branch_groups[sha].append(name.removeprefix("origin/"))
    if not branch_groups: raise RuntimeError("no remote branch refs were fetched")

    donor_tree=parse_tree(donor_sha); candidate_tree=parse_tree(candidate_sha)
    missing=[p for p in donor_paths if p not in donor_tree]
    if missing: raise RuntimeError(f"donor tree missing {len(missing)} paths: {missing[:10]}")

    tip_trees={}; blob_occurrences=collections.defaultdict(list); tip_entries={}
    for tip in sorted(branch_groups):
        tree=parse_tree(tip); tip_trees[tip]=tree; tip_entries[tip]=len(tree)
        for path,blob in tree.items():
            if is_text_path(path): blob_occurrences[blob].append((tip,path))

    donor_blob_ids=sorted({donor_tree[p] for p in donor_paths})
    donor_blobs=cat_file_batch(donor_blob_ids)
    symbol_to_donors=collections.defaultdict(set); symbols_by_donor={}
    for path in donor_paths:
        text=donor_blobs[donor_tree[path]].decode("utf-8",errors="replace")
        syms=extract_symbols(text,path); symbols_by_donor[path]=syms
        for symbol in syms: symbol_to_donors[symbol].add(path)
    symbols=sorted(symbol_to_donors,key=lambda x:(-len(x),x))
    symbol_patterns=[re.compile(r"(?<![A-Za-z0-9_])(?:"+"|".join(re.escape(s) for s in symbols[i:i+350])+r")(?![A-Za-z0-9_])") for i in range(0,len(symbols),350)]
    path_pattern=re.compile("|".join(re.escape(p) for p in sorted(donor_paths,key=len,reverse=True)))

    path_matches={}; symbol_matches={}; all_blob_ids=sorted(blob_occurrences)
    scanned=0; skipped_binary=0
    for offset in range(0,len(all_blob_ids),400):
        batch=cat_file_batch(all_blob_ids[offset:offset+400])
        for blob,raw in batch.items():
            scanned+=1
            if b"\0" in raw: skipped_binary+=1; continue
            text=raw.decode("utf-8",errors="replace"); occs=blob_occurrences[blob]
            for m in path_pattern.finditer(text):
                donor_path=m.group(0); line=text.count("\n",0,m.start())+1
                for tip,consumer in occs:
                    if consumer in AUDIT_TOOL_PATHS or consumer==donor_path: continue
                    key=(donor_path,consumer,category(consumer))
                    rec=path_matches.setdefault(key,{"tips":set(),"branches":set(),"lines":set(),"blob":blob})
                    rec["tips"].add(tip); rec["branches"].update(branch_groups[tip])
                    if len(rec["lines"])<20: rec["lines"].add(line)
            found=collections.defaultdict(set)
            for pattern in symbol_patterns:
                for m in pattern.finditer(text):
                    sym=m.group(0)
                    if len(found[sym])<20: found[sym].add(text.count("\n",0,m.start())+1)
            for sym,lines in found.items():
                for donor_path in symbol_to_donors[sym]:
                    for tip,consumer in occs:
                        if consumer in AUDIT_TOOL_PATHS or consumer==donor_path: continue
                        key=(donor_path,sym,consumer,category(consumer))
                        rec=symbol_matches.setdefault(key,{"tips":set(),"branches":set(),"lines":set(),"blob":blob})
                        rec["tips"].add(tip); rec["branches"].update(branch_groups[tip]); rec["lines"].update(lines)

    out=pathlib.Path(args.output); out.mkdir(parents=True,exist_ok=True)
    path_rows=[]
    for path in donor_paths:
        donor_blob=donor_tree[path]; candidate_blob=candidate_tree.get(path,"")
        status="CANDIDATE_ABSENT" if not candidate_blob else ("IDENTICAL" if candidate_blob==donor_blob else "DIVERGENT")
        present=[tip for tip,t in tip_trees.items() if path in t]
        versions={tip_trees[tip][path] for tip in present}
        identical=[tip for tip in present if tip_trees[tip][path]==donor_blob]
        divergent=[tip for tip in present if tip_trees[tip][path]!=donor_blob]
        absent=[tip for tip,t in tip_trees.items() if path not in t]
        path_rows.append({"donor_path":path,"donor_blob":donor_blob,"candidate_blob":candidate_blob,"candidate_status":status,
          "tips_present":len(present),"tips_absent":len(absent),"unique_blob_versions_across_tips":len(versions),
          "tips_with_donor_identical_blob":len(identical),"tips_with_divergent_blob":len(divergent),
          "branches_with_path":";".join(sorted({b for tip in present for b in branch_groups[tip]})),
          "branches_without_path":";".join(sorted({b for tip in absent for b in branch_groups[tip]})),
          "donor_symbols_extracted":len(symbols_by_donor[path])})
    write_csv(out/"donor_path_presence.csv",list(path_rows[0].keys()),path_rows)

    tip_rows=[{"tip_sha":tip,"branch_count":len(names),"branches":";".join(sorted(names)),"tree_entries":tip_entries[tip],
      "is_donor_tip":tip==donor_sha,"is_candidate_tip":tip==candidate_sha} for tip,names in sorted(branch_groups.items())]
    write_csv(out/"unique_branch_tips.csv",list(tip_rows[0].keys()),tip_rows)

    path_rows2=[]
    for (donor_path,consumer,cat),rec in sorted(path_matches.items()):
        path_rows2.append({"donor_path":donor_path,"consumer_path":consumer,"category":cat,"unique_tip_count":len(rec["tips"]),
          "tip_shas":";".join(sorted(rec["tips"])),"branch_names":";".join(sorted(rec["branches"])),
          "line_numbers_sample":";".join(map(str,sorted(rec["lines"]))),"consumer_blob":rec["blob"]})
    write_csv(out/"exact_path_reference_matches.csv",
      ["donor_path","consumer_path","category","unique_tip_count","tip_shas","branch_names","line_numbers_sample","consumer_blob"],path_rows2)

    symbol_rows=[]
    for (donor_path,symbol,consumer,cat),rec in sorted(symbol_matches.items()):
        symbol_rows.append({"donor_path":donor_path,"symbol":symbol,"consumer_path":consumer,"category":cat,
          "unique_tip_count":len(rec["tips"]),"tip_shas":";".join(sorted(rec["tips"])),
          "branch_names":";".join(sorted(rec["branches"])),"line_numbers_sample":";".join(map(str,sorted(rec["lines"]))),
          "consumer_blob":rec["blob"]})
    write_csv(out/"candidate_symbol_consumer_matches.csv",
      ["donor_path","symbol","consumer_path","category","unique_tip_count","tip_shas","branch_names","line_numbers_sample","consumer_blob"],symbol_rows)

    status=collections.Counter(r["candidate_status"] for r in path_rows)
    summary={"schema_version":1,"repository":inputs["repository"],"pr97":inputs["pr_number"],
      "donor_base_sha":inputs["donor_base_sha"],"donor_sha":donor_sha,"candidate_pr":inputs["candidate_pr_number"],
      "candidate_sha":candidate_sha,"remote_branch_ref_count":sum(len(v) for v in branch_groups.values()),
      "unique_branch_tip_count":len(branch_groups),"duplicate_tip_group_count":sum(1 for v in branch_groups.values() if len(v)>1),
      "donor_path_count":len(donor_paths),"candidate_same_path_status":dict(status),
      "unique_text_blob_count":len(blob_occurrences),"scanned_blob_count":scanned,"binary_blob_count_skipped":skipped_binary,
      "donor_symbol_count":len(symbols),"exact_path_reference_match_rows":len(path_rows2),
      "candidate_symbol_consumer_match_rows":len(symbol_rows),
      "limitations":["Path and identifier matches are candidate reverse-consumer evidence, not semantic consumer proof.",
        "A same-path divergent blob is not a semantic successor.","An absent same-path artifact may have an alternate successor elsewhere.",
        "Comments, documentation and tests can produce lexical matches; inspect category and exact source context.",
        "This scan makes no retirement, non-adoption, authority or source-baseline decisions."]}
    (out/"summary.json").write_text(json.dumps(summary,indent=2)+"\n",encoding="utf-8")
    report=["# DF-02 all-ref source-content consumer discovery","",f"- Donor PR #97 HEAD: {donor_sha}",
      f"- Candidate PR #192 HEAD: {candidate_sha}",f"- Branch refs scanned: {summary['remote_branch_ref_count']}",
      f"- Unique branch tips scanned: {summary['unique_branch_tip_count']}",f"- Donor paths: {len(donor_paths)}",
      f"- Candidate same-path status: {dict(status)}",f"- Unique text blobs indexed: {len(blob_occurrences)}",
      f"- Blobs scanned: {scanned}; binary blobs skipped: {skipped_binary}",f"- Extracted donor identifiers: {len(symbols)}",
      f"- Exact path-reference candidate rows: {len(path_rows2)}",f"- Symbol-consumer candidate rows: {len(symbol_rows)}","",
      "## Interpretation boundary","",
      "This artifact is a repository-wide lexical discovery index across fetched branch refs. It is not an automated semantic disposition. Each candidate match must be inspected at its exact branch tip and classified as a real consumer, test, build/workflow dependency, documentation reference, incidental token match or false positive. A missing match is not proof of no semantic successor.",
      "","## Outputs","",
      "- donor_path_presence.csv: exact path/blob presence and version counts by unique tip.",
      "- unique_branch_tips.csv: all remote branch names grouped by exact tip SHA.",
      "- exact_path_reference_matches.csv: exact donor path strings found in other files.",
      "- candidate_symbol_consumer_matches.csv: candidate identifier matches with exact branch/path/line samples.",
      "- summary.json: machine-readable scan counts and limitations.","",
      "No semantic successor, retirement, non-adoption, Project Director authority or implementation-baseline decision is made by this workflow."]
    (out/"report.md").write_text("\n".join(report)+"\n",encoding="utf-8")
    (out/"scanner.sha256").write_text(hashlib.sha256(pathlib.Path(__file__).read_bytes()).hexdigest()+"\n",encoding="utf-8")
    print(json.dumps(summary,indent=2))
    return 0

if __name__=="__main__":
    try: raise SystemExit(main())
    except Exception as exc:
        print(f"DF-02 scan failed: {exc}",file=sys.stderr)
        raise
