#include "jarvis/core/evolution_orchestrator.hpp"

#include <algorithm>
#include <cstdint>
#include <sstream>

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
    bool system_idle) const noexcept {
    EvolutionOrchestrationResult result;
    result.schedule = scheduler_.evaluate(now, last_run, system_idle);
    if (!result.schedule.allowed || opportunity.id.empty() || !generator ||
        !baseline_executor || !candidate_executor) {
        return result;
    }

    const auto candidates = EvolutionCandidateValidator::validate(generator(opportunity));
    if (candidates.empty()) return result;

    const auto ranked = EvolutionStrategy::rank(candidates, history);
    const std::size_t limit = std::min(result.schedule.trial_budget, ranked.size());
    result.experiments.reserve(limit);

    for (std::size_t index = 0; index < limit; ++index) {
        const auto& ranked_candidate = ranked[index];
        const auto proposal_it = std::find_if(
            candidates.begin(), candidates.end(),
            [&](const auto& proposal) { return proposal.key == ranked_candidate.parameter_key; });
        if (proposal_it == candidates.end()) continue;

        EvolutionExperiment experiment;
        experiment.id = experiment_id(opportunity, *proposal_it, index);
        experiment.proposal = *proposal_it;
        EvolutionExperimentCoordinator::run(
            experiment, sandbox, baseline_executor, candidate_executor, trial_config_);
        result.experiments.push_back(std::move(experiment));
    }
    return result;
}

} // namespace jarvis::core
