from __future__ import annotations
import json, os, tempfile
from pathlib import Path
from typing import Any, Iterator

class ContinuityLog:
    """Append-only history plus atomic snapshots for cognitive continuity."""
    def __init__(self,root:str|Path)->None:
        self.root=Path(root); self.root.mkdir(parents=True,exist_ok=True)
        self.events_path=self.root/"events.jsonl"; self.snapshot_path=self.root/"snapshot.json"
    def append(self,event:dict[str,Any])->None:
        with self.events_path.open("a",encoding="utf-8") as h:
            h.write(json.dumps(event,separators=(",",":"),ensure_ascii=False)+"\n"); h.flush(); os.fsync(h.fileno())
    def events(self)->Iterator[dict[str,Any]]:
        if not self.events_path.exists(): return
        with self.events_path.open(encoding="utf-8") as h:
            for line in h:
                if line.strip(): yield json.loads(line)
    def save_snapshot(self,state:dict[str,Any])->None:
        fd,tmp=tempfile.mkstemp(prefix="jarvis-state-",dir=self.root)
        try:
            with os.fdopen(fd,"w",encoding="utf-8") as h:
                json.dump(state,h,separators=(",",":"),ensure_ascii=False); h.flush(); os.fsync(h.fileno())
            os.replace(tmp,self.snapshot_path)
        finally:
            if os.path.exists(tmp): os.unlink(tmp)
    def load_snapshot(self)->dict[str,Any]|None:
        if not self.snapshot_path.exists(): return None
        with self.snapshot_path.open(encoding="utf-8") as h: return json.load(h)
