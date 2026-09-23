import type {
  AgentBridgeRequest,
  AgentBridgeSession,
  AgentMessage,
  AgentMessageType,
} from "./agent_bridge";

/**
 * Supervised human/ChatGPT-facing session over the existing agent transport.
 * Communication never grants execution authority; authorization remains inside
 * the engineering/runtime boundary.
 */
export interface OperatorSession {
  readonly operatorId: string;
  readonly runId: string;
  readonly workspaceId: string;
  readonly session: AgentBridgeSession;
}

export interface OperatorAgentRequest {
  readonly recipientId: string;
  readonly correlationId: string;
  readonly type?: Extract<AgentMessageType, "request" | "query" | "feedback">;
  readonly payload: AgentBridgeRequest["payload"];
}

export function createOperatorSession(
  session: AgentBridgeSession,
): OperatorSession {
  return {
    operatorId: session.participantId,
    runId: session.runId,
    workspaceId: session.workspaceId,
    session,
  };
}

export async function operatorSend(
  operator: OperatorSession,
  request: OperatorAgentRequest,
): Promise<void> {
  await operator.session.transport.send({
    recipientId: request.recipientId,
    correlationId: request.correlationId,
    type: request.type ?? "request",
    payload: request.payload,
  });
}

export async function operatorReceive(
  operator: OperatorSession,
): Promise<readonly AgentMessage[]> {
  return operator.session.transport.receive();
}

export async function operatorConnected(
  operator: OperatorSession,
): Promise<boolean> {
  return operator.session.transport.connected();
}
