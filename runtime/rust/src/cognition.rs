use std::collections::HashMap;

#[derive(Clone, Debug, PartialEq)]
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
        let strength = evidence_strength.clamp(0.0, 1.0);
        match self.beliefs.get_mut(&key) {
            Some(existing) if existing.value == value => {
                let n = existing.evidence as f64;
                existing.strength = ((existing.strength * n) + strength) / (n + 1.0);
                existing.evidence += 1;
            }
            Some(existing) if strength > existing.strength => {
                existing.value = value.clone();
                existing.strength = strength;
                existing.evidence += 1;
            }
            Some(existing) => {
                existing.strength = (existing.strength * 0.95).max(0.0);
                existing.evidence += 1;
            }
            None => {
                self.beliefs.insert(key.clone(), Belief { key, value: value.clone(), strength, evidence: 1 });
            }
        }
        self.cycle += 1;
        self.working_memory.push(value);
        if self.working_memory.len() > 64 {
            self.working_memory.remove(0);
        }
    }
}
