use crate::error::{RuntimeError, RuntimeResult};

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct SecurityPolicy {
    pub require_network_isolation: bool,
    pub require_filesystem_isolation: bool,
    pub require_privilege_drop: bool,
    pub require_no_new_privileges: bool,
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct IsolationCapabilities {
    pub network_isolation: bool,
    pub filesystem_isolation: bool,
    pub privilege_drop: bool,
    pub no_new_privileges: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum IsolationDecision {
    Allowed,
    Rejected,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct SecurityRuntime {
    policy: SecurityPolicy,
    capabilities: IsolationCapabilities,
}

impl SecurityRuntime {
    pub fn new(policy: SecurityPolicy, capabilities: IsolationCapabilities) -> Self {
        Self { policy, capabilities }
    }

    pub fn evaluate(&self) -> RuntimeResult<IsolationDecision> {
        if self.policy.require_network_isolation && !self.capabilities.network_isolation {
            return Err(RuntimeError::Unavailable("network isolation is unavailable".into()));
        }
        if self.policy.require_filesystem_isolation && !self.capabilities.filesystem_isolation {
            return Err(RuntimeError::Unavailable("filesystem isolation is unavailable".into()));
        }
        if self.policy.require_privilege_drop && !self.capabilities.privilege_drop {
            return Err(RuntimeError::Unavailable("privilege drop is unavailable".into()));
        }
        if self.policy.require_no_new_privileges && !self.capabilities.no_new_privileges {
            return Err(RuntimeError::Unavailable("no-new-privileges is unavailable".into()));
        }
        Ok(IsolationDecision::Allowed)
    }

    pub fn policy(&self) -> SecurityPolicy { self.policy }
    pub fn capabilities(&self) -> IsolationCapabilities { self.capabilities }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn fails_closed_when_required_capability_is_missing() {
        let runtime = SecurityRuntime::new(
            SecurityPolicy {
                require_network_isolation: true,
                ..SecurityPolicy::default()
            },
            IsolationCapabilities::default(),
        );
        assert!(runtime.evaluate().is_err());
    }

    #[test]
    fn allows_when_required_capabilities_exist() {
        let runtime = SecurityRuntime::new(
            SecurityPolicy {
                require_no_new_privileges: true,
                ..SecurityPolicy::default()
            },
            IsolationCapabilities {
                no_new_privileges: true,
                ..IsolationCapabilities::default()
            },
        );
        assert_eq!(runtime.evaluate().unwrap(), IsolationDecision::Allowed);
    }
}
