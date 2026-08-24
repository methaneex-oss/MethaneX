# MethaneX JARVIS prototype testing

## 1. Install

Use Python 3.11+.

```bash
git clone https://github.com/methaneex-oss/MethaneX.git
cd MethaneX
```

No external AI provider is required for the first smoke test.

## 2. Run automated tests

```bash
python -m unittest discover -s tests -v
```

## 3. Start the integrated runtime

```bash
python -m methane_x.jarvis
```

The first runtime uses console I/O as the hardware-independent speech boundary. The speech interface is intentionally replaceable; microphone STT/TTS adapters are not forced into the core dependency set.

Try:

```text
Jarvis status
Jarvis remember my prototype is called MethaneX
Jarvis recall MethaneX
Jarvis shutdown
```

## 4. What this milestone proves

- persistent SQLite memory survives process restarts;
- tiered memory contracts exist (Tier 1 identity, Tier 2 approved knowledge/preferences, Tier 3 experience);
- wake-word gating is present at the runtime boundary;
- reasoning is provider-independent through `IntelligenceProvider`;
- a learning engine can turn observed outcomes into candidate lessons;
- tools can be registered and executed through the action loop;
- the system remains usable without an external model.

## 5. Not yet complete

Real microphone STT, natural neural TTS, computer vision, autonomous model selection, broad device control, and advanced self-improvement are subsequent milestones. They should plug into these interfaces rather than replace the core.
