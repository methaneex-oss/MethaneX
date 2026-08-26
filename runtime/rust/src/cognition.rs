use std::collections::HashMap;

#[derive(Clone, Debug)]
pub struct Belief {
    pub key: String,
    pub value: String,
    pub strength: f64,
    pub evidence: u64,
}

#[derive(Default, Debug)]
pub struct CognitiveState {
    pub cycle: u64,
    pub beliefs: HashMap<String, Belief>,
    pub working_memory: Vec<String>,
}

impl CognitiveState {
    pub fn observe(&mut self, key: impl Into<String>, value: impl Into<String>, evidence_strength: f64) {
        let key = key.into();
        let value = value.into();
        match self.beliefs.get_mut(&key) {
            Some(existing) if existing.value == value => {
                let n = existing.evidence as f64;
                existing.strength = ((existing.strength * n) + evidence_strength) / (n + 1.0);
                existing.evidence += 1;
            }
            Some(existing) if evidence_strength > existing.strength => {
                existing.value = value;
                existing.strength = evidence_strength;
                existing.evidence += 1;
            }
            Some(existing) => {
                existing.strength *= 0.95;
            }
            None => {
                self.beliefs.insert(key.clone(), Belief { key, value, strength: evidence_strength, evidence: 1 });
            }
        }
        self.cycle += 1;
        self.working_memory.push(value);
        if self.working_memory.len() > 64 {
            self.working_memory.remove(0);
        }
    }
}
