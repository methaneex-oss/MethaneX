from __future__ import annotations
from dataclasses import dataclass,field,asdict
from time import time_ns
from typing import Any

@dataclass(frozen=True,slots=True)
class Fact:
    subject:str; predicate:str; value:Any; strength:float=.5; source:str="unknown"; observed_ns:int=field(default_factory=time_ns)
@dataclass(frozen=True,slots=True)
class Relation:
    subject:str; predicate:str; object:str; strength:float=.5; source:str="inferred"; observed_ns:int=field(default_factory=time_ns)

class WorldModel:
    def __init__(self)->None: self.facts={}; self.relations={}
    def observe_fact(self,subject:str,predicate:str,value:Any,*,strength:float=.7,source:str="observation")->Fact:
        key=(subject,predicate); old=self.facts.get(key)
        if old is None: fact=Fact(subject,predicate,value,max(0,min(1,strength)),source)
        elif old.value==value: fact=Fact(subject,predicate,value,min(.999,old.strength+(1-old.strength)*strength*.35),source)
        else: fact=Fact(subject,predicate,value,max(.05,min(.95,strength*.75)),source)
        self.facts[key]=fact; return fact
    def relate(self,subject:str,predicate:str,object:str,*,strength:float=.5,source:str="inferred")->Relation:
        r=Relation(subject,predicate,object,max(0,min(1,strength)),source); self.relations[(subject,predicate,object)]=r; return r
    def get_fact(self,subject:str,predicate:str)->Fact|None: return self.facts.get((subject,predicate))
    def related(self,subject:str,predicate:str|None=None)->list[Relation]: return [r for r in self.relations.values() if r.subject==subject and (predicate is None or r.predicate==predicate)]
    def query(self,subject:str|None=None,predicate:str|None=None)->list[Fact]: return [f for f in self.facts.values() if (subject is None or f.subject==subject) and (predicate is None or f.predicate==predicate)]
    def export(self)->dict[str,list[dict[str,Any]]]: return {"facts":[asdict(f) for f in self.facts.values()],"relations":[asdict(r) for r in self.relations.values()]}
    def restore(self,data:dict[str,list[dict[str,Any]]])->None:
        self.facts={(f['subject'],f['predicate']):Fact(**f) for f in data.get('facts',[])}; self.relations={(r['subject'],r['predicate'],r['object']):Relation(**r) for r in data.get('relations',[])}
