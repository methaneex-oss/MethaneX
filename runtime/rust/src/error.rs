#[derive(Debug, Clone, PartialEq, Eq)]
pub enum RuntimeError {
    InvalidInput(String),
    Unavailable(String),
}

pub type RuntimeResult<T> = Result<T, RuntimeError>;
