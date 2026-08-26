from __future__ import annotations
from dataclasses import dataclass
from .cognition import CandidateAction
from .causal import CausalModel
from .types import CognitiveState

@dataclass(frozen=True,slots=True)
class Decision:
    action:CandidateAction; score:float; rationale:tuple[str,...]
class DecisionEngine:
    def __init__(self,causal:CausalModel)->None: self.causal=causal
    def rank(self,state:CognitiveState,actions:list[CandidateAction])->list[Decision]:
        uncertainty=1-max((b.strength for b in state.beliefs.values()),default=0)
        out=[]
        for a in actions:
            exploration=uncertainty*max(0,a.reversibility); risk_cost=a.risk*(1-a.reversibility)
            score=a.utility+a.expected_value+exploration-risk_cost
            out.append(Decision(a,score,(f"utility={a.utility:.3f}",f"expected_value={a.expected_value:.3f}",f"risk={a.risk:.3f}",f"reversibility={a.reversibility:.3f}")))
        return sorted(out,key=lambda d:d.score,reverse=True)
