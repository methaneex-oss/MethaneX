pub mod cognition;

use cognition::CognitiveState;

pub struct BrainRuntime {
    pub state: CognitiveState,
}

impl BrainRuntime {
    pub fn new() -> Self {
        Self { state: CognitiveState::default() }
    }

    pub fn observe(&mut self, key: &str, value: &str, strength: f64) {
        self.state.observe(key, value, strength.clamp(0.0, 1.0));
    }
}

impl Default for BrainRuntime {
    fn default() -> Self { Self::new() }
}
