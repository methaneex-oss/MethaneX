from __future__ import annotations
from dataclasses import dataclass
from typing import Any
from .types import Belief

@dataclass(frozen=True, slots=True)
class Evidence:
    key: str
    value: Any
    reliability: float

def update_belief(belief: Belief | None, evidence: Evidence) -> Belief:
    reliability=min(1.0,max(0.0,evidence.reliability))
    if belief is None: return Belief(evidence.key,"observed_as",evidence.value,reliability)
    agreement=1.0 if belief.value==evidence.value else 0.0
    learning_rate=0.15+0.35*reliability
    new_strength=min(0.999,max(0.001,belief.strength+learning_rate*(agreement-belief.strength)))
    if evidence.value != belief.value and reliability > 0.5:
        return Belief(belief.subject,belief.predicate,evidence.value,min(0.95,0.5+0.5*reliability),belief.evidence_count+1)
    belief.strength=new_strength; belief.evidence_count+=1
    return belief

def novelty_score(observation: dict[str,Any], known: dict[str,Any]) -> float:
    if not observation: return 0.0
    return sum(known.get(k)!=v for k,v in observation.items())/len(observation)

def surprise(predicted: float, observed: float, scale: float=1.0) -> float:
    if scale<=0: raise ValueError("scale must be positive")
    return min(1.0,abs(predicted-observed)/scale)
