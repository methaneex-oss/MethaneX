from __future__ import annotations
from dataclasses import dataclass
from typing import Any

@dataclass(frozen=True,slots=True)
class CausalRule:
    cause:str; effect:str; strength:float=.5; observations:int=0
@dataclass(frozen=True,slots=True)
class Scenario:
    assumptions:dict[str,Any]; predicted:dict[str,Any]; support:float

class CausalModel:
    def __init__(self)->None: self.rules={}
    def observe_transition(self,before:dict[str,Any],after:dict[str,Any])->list[CausalRule]:
        cb={k:v for k,v in before.items() if k in after and before[k]!=after[k]}; ca={k:v for k,v in after.items() if k not in before or before[k]!=after[k]}; learned=[]
        for cause,cv in cb.items():
            for effect,ev in ca.items():
                key=(f"{cause}={cv}",f"{effect}={ev}"); old=self.rules.get(key)
                rule=CausalRule(key[0],key[1],.55,1) if old is None else CausalRule(old.cause,old.effect,min(.999,old.strength+.08*(1-old.strength)),old.observations+1)
                self.rules[key]=rule; learned.append(rule)
        return learned
    def counterfactual(self,assumptions:dict[str,Any])->Scenario:
        predicted={}; supports=[]
        for r in self.rules.values():
            k,_,v=r.cause.partition('=')
            if assumptions.get(k)==v:
                ek,_,ev=r.effect.partition('='); predicted[ek]=ev; supports.append(r.strength)
        return Scenario(dict(assumptions),predicted,sum(supports)/len(supports) if supports else 0)
    def export(self)->list[dict[str,Any]]: return [{"cause":r.cause,"effect":r.effect,"strength":r.strength,"observations":r.observations} for r in self.rules.values()]
    def restore(self,data:list[dict[str,Any]])->None: self.rules={(r['cause'],r['effect']):CausalRule(**r) for r in data}
