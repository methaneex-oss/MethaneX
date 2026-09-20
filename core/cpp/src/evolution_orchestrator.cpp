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
        const auto batch = EvolutionExperimentCoordinator::run(
            experiment, sandbox, baseline_executor, candidate_executor, trial_config_);
        if (!batch.executed) {
            result.lifecycle.push_back(EvolutionLifecycleState::EvaluationRejected);
            ++result.rejected;
            result.experiments.push_back(std::move(experiment));
            continue;
        }

        result.lifecycle.push_back(EvolutionLifecycleState::CandidateEvaluated);
        if (controller == nullptr) {
            if (experiment.outcome == ExperimentOutcome::Improved) {
                ++result.adopted;
                result.lifecycle.back() = EvolutionLifecycleState::Adopted;
            } else {
                ++result.rejected;
            }
        } else {
            if (!controller->record_evaluation(experiment)) {
                result.lifecycle.back() = EvolutionLifecycleState::EvaluationRejected;
                ++result.rejected;
            } else if (experiment.outcome != ExperimentOutcome::Improved) {
                result.lifecycle.back() = EvolutionLifecycleState::SafetyRejected;
                ++result.rejected;
            } else if (controller->adopt(experiment)) {
                result.lifecycle.back() = EvolutionLifecycleState::Adopted;
                ++result.adopted;
            } else {
                result.lifecycle.back() = EvolutionLifecycleState::SafetyRejected;
                ++result.rejected;
            }
        }

        result.experiments.push_back(std::move(experiment));
    }

    return result;
}

} // namespace jarvis::core
