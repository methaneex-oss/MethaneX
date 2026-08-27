pub mod cognition;
pub mod error;

use cognition::CognitiveState;
use error::{RuntimeError, RuntimeResult};

pub struct BrainRuntime {
    pub state: CognitiveState,
}

impl BrainRuntime {
    pub fn new() -> Self {
        Self { state: CognitiveState::default() }
    }

    pub fn observe(&mut self, key: &str, value: &str, strength: f64) -> RuntimeResult<()> {
        if key.trim().is_empty() {
            return Err(RuntimeError::InvalidInput("observation key cannot be empty".into()));
        }
        if value.trim().is_empty() {
            return Err(RuntimeError::InvalidInput("observation value cannot be empty".into()));
        }
        if !strength.is_finite() {
            return Err(RuntimeError::InvalidInput("observation strength must be finite".into()));
        }
        self.state.observe(key, value, strength);
        Ok(())
    }
}

impl Default for BrainRuntime {
    fn default() -> Self { Self::new() }
}
