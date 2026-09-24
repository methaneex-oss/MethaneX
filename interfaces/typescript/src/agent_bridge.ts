import type { Primitive } from "./brain";
export type AgentMessageType = "request" | "artifact" | "review" | "feedback" | "status" | "query" | "result" | "error";
export interface AgentMessage { readonly messageId:string; readonly sequence:bigint; readonly runId:string; readonly workspaceId:string; readonly senderId:string; readonly recipientId:string; readonly correlationId:string; readonly type:AgentMessageType; readonly payload:Record<string,Primitive>|string; }
export interface AgentBridgeRequest { readonly recipientId:string; readonly correlationId:string; readonly type:Extract<AgentMessageType,"request"|"query"|"feedback">; readonly payload:Record<string,Primitive>|string; }
export interface AgentBridgeTransport { send(request:AgentBridgeRequest):Promise<void>; receive():Promise<readonly AgentMessage[]>; connected():Promise<boolean>; }
export interface AgentBridgeSession { readonly participantId:string; readonly runId:string; readonly workspaceId:string; readonly transport:AgentBridgeTransport; }
