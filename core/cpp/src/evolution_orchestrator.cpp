#include "jarvis/core/evolution_orchestrator.hpp"

#include <algorithm>
#include <exception>
#include <sstream>
#include <utility>

namespace jarvis::core {
namespace {

std::string experiment_id(const EvolutionOpportunity& opportunity,
                          const EvolutionProposal& proposal,
                          std::size_t ordinal) {
    std::ostringstream out;
    out << opportunity.id << ":" << proposal.key << ":" << ordinal;
    return out.str();
}

} // namespace

EvolutionOrchestrator::EvolutionOrchestrator(EvolutionSchedulePolicy policy)
    : scheduler_(policy) {}

EvolutionOrchestrationResult EvolutionOrchestrator::run(
    const EvolutionOpportunity& opportunity,
    const EvolutionCandidateGenerator& generator,
    const EvolutionSandbox& sandbox,
    const CandidateExecutor& baseline_executor,
    const CandidateExecutor& candidate_executor,
    const EvolutionHistory& history,
    std::chrono::steady_clock::time_point now,
    std::chrono::steady_clock::time_point last_run,
    bool system_idle,
    EvolutionController* controller) const noexcept {
    EvolutionOrchestrationResult result;
    result.schedule = scheduler_.evaluate(now, last_run, system_idle);
    if (!result.schedule.allowed || opportunity.id.empty() || !generator ||
        !baseline_executor || !candidate_executor) {
        return result;
    }

    std::vector<EvolutionProposal> generated;
    try {
        generated = generator(opportunity);
    } catch (...) {
        return result;
    }

    const auto candidates = EvolutionCandidateValidator::validate(generated);
    if (candidates.empty()) return result;

    const auto ranked = EvolutionStrategy::rank(candidates, history);
    const std::size_t limit = std::min(result.schedule.trial_budget, ranked.size());
    result.experiments.reserve(limit);
    result.lifecycle.reserve(limit);

    for (std::size_t index = 0; index < limit; ++index) {
        const auto& ranked_candidate = ranked[index];
        const auto proposal_it = std::find_if(
            candidates.begin(), candidates.end(),
            [&](const auto& proposal) { return proposal.key == ranked_candidate.parameter_key; });
        if (proposal_it == candidates.end()) continue;

        EvolutionExperiment experiment;
        experiment.id = experiment_id(opportunity, *proposal_it, index);
        experiment.proposal = *proposal_it;
        const auto batch = EvolutionExperimentCoordinator::run(
            experiment, sandbox, baseline_executor, candidate_executor, trial_config_);
        if (batch.executed) experiment.candidate_executed = true;

        if (!batch.executed) {
            result.lifecycle.push_back(EvolutionLifecycleState::EvaluationRejected);
            ++result.rejected;
        } else {
            result.lifecycle.push_back(EvolutionLifecycleState::CandidateEvaluated);
        }
        result.experiments.push_back(std::move(experiment));
    }

    if (result.experiments.empty()) return result;

    // Evaluate every candidate first, then adopt at most one empirical winner.
    // This prevents multiple simultaneous changes from sharing one canary stream.
    std::size_t winner = result.experiments.size();
    double winner_gain = 0.0;
    for (std::size_t i = 0; i < result.experiments.size(); ++i) {
        auto& experiment = result.experiments[i];
        if (experiment.outcome != ExperimentOutcome::Improved) continue;
        const double gain = experiment.candidate_fitness - experiment.baseline_fitness;
        if (winner == result.experiments.size() || gain > winner_gain ||
            (gain == winner_gain && experiment.confidence > result.experiments[winner].confidence)) {
            winner = i;
            winner_gain = gain;
        }
    }

    for (std::size_t i = 0; i < result.experiments.size(); ++i) {
        auto& experiment = result.experiments[i];
        if (controller != nullptr && experiment.candidate_executed) {
            if (!controller->record_evaluation(experiment)) {
                result.lifecycle[i] = EvolutionLifecycleState::EvaluationRejected;
                ++result.rejected;
            }
        }
    }

    if (winner == result.experiments.size()) {
        for (std::size_t i = 0; i < result.experiments.size(); ++i) {
            if (result.lifecycle[i] == EvolutionLifecycleState::CandidateEvaluated) ++result.rejected;
        }
        return result;
    }

    for (std::size_t i = 0; i < result.experiments.size(); ++i) {
        if (i == winner) continue;
        if (result.lifecycle[i] == EvolutionLifecycleState::CandidateEvaluated) {
            result.lifecycle[i] = EvolutionLifecycleState::Superseded;
            ++result.rejected;
        }
    }

    if (controller == nullptr) {
        result.lifecycle[winner] = EvolutionLifecycleState::Superseded;
        ++result.rejected;
        return result;
    }

    auto& selected = result.experiments[winner];
    if (controller->adopt(selected)) {
        result.lifecycle[winner] = EvolutionLifecycleState::Canarying;
        CanaryDecision canary{};
        for (std::size_t i = 0; i < 3; ++i) {
            canary = controller->observe_canary(
                selected.proposal.key, selected.id,
                CanaryObservation{selected.baseline_fitness, selected.candidate_fitness});
            if (canary.rollback) {
                result.lifecycle[winner] = EvolutionLifecycleState::RolledBack;
                ++result.rejected;
                return result;
            }
        }
        result.lifecycle[winner] = canary.sufficient_evidence
            ? EvolutionLifecycleState::Retained
            : EvolutionLifecycleState::Canarying;
        if (result.lifecycle[winner] == EvolutionLifecycleState::Retained) ++result.adopted;
    } else {
        result.lifecycle[winner] = EvolutionLifecycleState::SafetyRejected;
        ++result.rejected;
    }

    return result;
}

} // namespace jarvis::core
