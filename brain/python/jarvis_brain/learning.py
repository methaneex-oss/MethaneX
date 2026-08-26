from __future__ import annotations
from dataclasses import dataclass
from typing import Any

@dataclass(slots=True)
class LearnedPattern:
    key: str; estimate: float; observations: int=0; mean_error: float=0.0

class ExperienceLearner:
    def __init__(self)->None: self.patterns: dict[str,LearnedPattern]={}
    def observe(self,key:str,predicted:float,actual:float)->LearnedPattern:
        if not 0<=predicted<=1 or not 0<=actual<=1: raise ValueError("predicted and actual values must be in [0, 1]")
        pattern=self.patterns.get(key)
        if pattern is None: pattern=LearnedPattern(key,predicted); self.patterns[key]=pattern
        error=actual-predicted; step=1/(pattern.observations+2)
        pattern.estimate=min(1,max(0,pattern.estimate+step*error)); pattern.observations+=1
        pattern.mean_error+=(abs(error)-pattern.mean_error)/pattern.observations
        return pattern
    def restore(self,data:dict[str,dict[str,Any]])->None:
        self.patterns={k:LearnedPattern(k,float(v.get('estimate',.5)),int(v.get('observations',0)),float(v.get('mean_error',0))) for k,v in data.items()}
    def export(self)->dict[str,dict[str,Any]]:
        return {k:{"estimate":v.estimate,"observations":v.observations,"mean_error":v.mean_error} for k,v in self.patterns.items()}
