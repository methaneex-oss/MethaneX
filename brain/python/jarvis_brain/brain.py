from __future__ import annotations
from dataclasses import asdict
from pathlib import Path
from typing import Any
from .causal import CausalModel,Scenario
from .cognition import CandidateAction
from .continuity import ContinuityLog
from .decision import Decision,DecisionEngine
from .learning import ExperienceLearner
from .reasoning import Evidence,novelty_score,update_belief
from .types import Belief,CognitiveState,EventKind,Prediction
from .world_model import WorldModel

class Brain:
    def __init__(self,data_root:str|Path="data/continuity")->None:
        self.state=CognitiveState(); self.continuity=ContinuityLog(data_root); self.learner=ExperienceLearner(); self.world=WorldModel(); self.causal=CausalModel(); self.decision=DecisionEngine(self.causal); self._restore()
    def observe(self,observation:dict[str,Any],*,source:str="unknown")->dict[str,Any]:
        previous={k.removeprefix("world:"):b.value for k,b in self.state.beliefs.items() if k.startswith("world:")}; self.state.cycle+=1; self.state.events_seen+=1; self.state.active_context={"source":source,"observation":observation}; self.state.working_memory.append({"cycle":self.state.cycle,**observation}); self.state.bounded_working_memory()
        known={k.removeprefix("world:"):b.value for k,b in self.state.beliefs.items() if k.startswith("world:") and b.strength>=.5}; novelty=novelty_score(observation,known)
        for k,v in observation.items(): self.state.beliefs[f"world:{k}"]=update_belief(self.state.beliefs.get(f"world:{k}"),Evidence(f"world:{k}",v,.7)); self.world.observe_fact("world",k,v,strength=.7,source=source)
        self.causal.observe_transition(previous,observation); self._record(EventKind.OBSERVATION,{"source":source,"observation":observation,"novelty":novelty}); self._persist(); return {"cycle":self.state.cycle,"novelty":novelty}
    def predict(self,key:str,value:Any,basis:list[str])->Prediction:
        p=Prediction(key,value,tuple(basis)); self.state.predictions[key]=p; self._record(EventKind.PREDICTION,{"key":key,"predicted_value":value,"basis":basis}); self._persist(); return p
    def simulate(self,assumptions:dict[str,Any])->Scenario:
        s=self.causal.counterfactual(assumptions); self._record(EventKind.SIMULATION,{"assumptions":assumptions,"predicted":s.predicted,"support":s.support}); self._persist(); return s
    def choose(self,actions:list[CandidateAction])->Decision|None:
        ranked=self.decision.rank(self.state,actions)
        if not ranked:return None
        selected=ranked[0]; self.record_action(selected.action); return selected
    def record_action(self,action:CandidateAction)->None:
        self._record(EventKind.ACTION,{"name":action.name,"arguments":action.arguments,"utility":action.utility,"expected_value":action.expected_value,"risk":action.risk,"reversibility":action.reversibility,"evidence":list(action.evidence)}); self._persist()
    def record_outcome(self,key:str,actual:Any)->float|None:
        p=self.state.predictions.get(key)
        if p is None or p.resolved:return None
        p.resolved=True
        if isinstance(p.predicted_value,(int,float)) and isinstance(actual,(int,float)):
            predicted=min(1,max(0,float(p.predicted_value))); observed=min(1,max(0,float(actual))); p.error=abs(observed-predicted); learned=self.learner.observe(key,predicted,observed); self.state.performance[f"prediction:{key}"]=1-learned.mean_error; self._record(EventKind.LEARNING,{"key":key,"predicted":predicted,"actual":observed,"error":p.error,"estimate":learned.estimate})
        else:p.error=0 if p.predicted_value==actual else 1; self._record(EventKind.OUTCOME,{"key":key,"actual":actual,"match":p.error==0})
        self._persist(); return p.error
    def snapshot(self)->dict[str,Any]:
        return {"identity":self.state.identity,"cycle":self.state.cycle,"active_context":self.state.active_context,"beliefs":{k:asdict(v) for k,v in self.state.beliefs.items()},"predictions":{k:asdict(v) for k,v in self.state.predictions.items()},"working_memory":self.state.working_memory,"capabilities":self.state.capabilities,"performance":self.state.performance,"events_seen":self.state.events_seen,"learned_patterns":self.learner.export(),"world_model":self.world.export(),"causal_model":self.causal.export()}
    def _record(self,kind:EventKind,payload:dict[str,Any])->None:self.continuity.append({"sequence":self.state.events_seen,"cycle":self.state.cycle,"kind":kind.value,"payload":payload})
    def _persist(self)->None:self.continuity.save_snapshot(self.snapshot())
    def _restore(self)->None:
        s=self.continuity.load_snapshot()
        if not s:return
        self.state.identity=s.get("identity",self.state.identity); self.state.cycle=s.get("cycle",0); self.state.active_context=s.get("active_context",{}); self.state.working_memory=s.get("working_memory",[]); self.state.capabilities=s.get("capabilities",{}); self.state.performance=s.get("performance",{}); self.state.events_seen=s.get("events_seen",0)
        for k,r in s.get("beliefs",{}).items():self.state.beliefs[k]=Belief(**r)
        for k,r in s.get("predictions",{}).items():r["basis"]=tuple(r.get("basis",())); self.state.predictions[k]=Prediction(**r)
        self.learner.restore(s.get("learned_patterns",{})); self.world.restore(s.get("world_model",{})); self.causal.restore(s.get("causal_model",[]))
