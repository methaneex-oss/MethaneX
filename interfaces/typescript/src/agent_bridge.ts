export type AgentMessageType =
  | "request"
  | "response"
  | "query"
  | "feedback"
  | "event";

export type AgentBridgePrimitive = string | number | boolean | null;
export type AgentBridgePayload = Readonly<Record<string, AgentBridgePrimitive | readonly AgentBridgePrimitive[]>>;

export interface AgentBridgeRequest {
  readonly recipientId: string;
  readonly correlationId: string;
  readonly type: Extract<AgentMessageType, "request" | "query" | "feedback">;
  readonly payload: AgentBridgePayload;
}

export interface AgentMessage {
  readonly messageId: string;
  readonly senderId: string;
  readonly recipientId: string;
  readonly runId: string;
  readonly workspaceId: string;
  readonly correlationId: string;
  readonly type: AgentMessageType;
  readonly payload: AgentBridgePayload;
  readonly createdAtNs: bigint;
}

export interface AgentBridgeTransport {
  send(message: Omit<AgentMessage, "messageId" | "senderId" | "runId" | "workspaceId" | "createdAtNs">): Promise<void>;
  receive(): Promise<readonly AgentMessage[]>;
  connected(): Promise<boolean>;
}

export interface AgentBridgeSession {
  readonly participantId: string;
  readonly runId: string;
  readonly workspaceId: string;
  readonly transport: AgentBridgeTransport;
}

/**
 * Creates a request envelope without assigning execution authority.
 * Authorization is deliberately handled by the execution boundary, not by
 * the conversational bridge.
 */
export function createAgentRequest(
  recipientId: string,
  correlationId: string,
  payload: AgentBridgePayload,
  type: Extract<AgentMessageType, "request" | "query" | "feedback"> = "request",
): AgentBridgeRequest {
  if (!recipientId || !correlationId) {
    throw new Error("recipientId and correlationId are required");
  }
  return { recipientId, correlationId, type, payload };
}
