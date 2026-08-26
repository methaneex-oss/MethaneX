from __future__ import annotations
from dataclasses import asdict,dataclass
from typing import Any,Iterable
from .brain import Brain
from .cognition import CandidateAction,build_context
from .types import EventKind

@dataclass(frozen=True,slots=True)
class CognitiveCycle:
    cycle:int; context:dict[str,Any]; novelty:float; selected_action:dict[str,Any]|None

class CognitiveRuntime:
    def __init__(self,brain:Brain|None=None)->None:self.brain=brain or Brain()
    def process(self,observation:dict[str,Any],*,source:str="unknown",actions:Iterable[CandidateAction]=())->CognitiveCycle:
        result=self.brain.observe(observation,source=source); context=build_context(observation,self.brain.state.working_memory); selected=self.brain.choose(list(actions))
        if selected is not None:self.brain._record(EventKind.DECISION,{"action":selected.action.name,"score":selected.score,"rationale":selected.rationale}); self.brain._persist()
        return CognitiveCycle(result["cycle"],context,result["novelty"],None if selected is None else asdict(selected))
