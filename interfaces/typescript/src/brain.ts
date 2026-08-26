export type Primitive = string | number | boolean | null;

export interface Observation {
  readonly source: string;
  readonly kind: string;
  readonly data: Record<string, Primitive>;
  readonly timestampNs: bigint;
}

export interface DecisionContext {
  readonly goal: string;
  readonly observations: readonly Observation[];
}

export interface Capability {
  readonly id: string;
  readonly version: string;
  readonly inputs: readonly string[];
  readonly outputs: readonly string[];
}

export interface BrainTransport {
  observe(observation: Observation): Promise<void>;
  decide(context: DecisionContext): Promise<string | null>;
  capabilities(): Promise<readonly Capability[]>;
}
