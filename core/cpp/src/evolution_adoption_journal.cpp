#include "jarvis/core/evolution_adoption_journal.hpp"

namespace jarvis::core {

bool EvolutionAdoptionJournal::stage(const EvolutionExperiment& experiment) {
    if (experiment.id.empty() || experiment.proposal.key.empty()) return false;
    std::lock_guard lock(mutex_);
    auto& r = records_[experiment.id];
    if (r.revision != 0 && r.state == AdoptionState::Adopted) return true;
    r.experiment_id = experiment.id;
    r.parameter_key = experiment.proposal.key;
    r.baseline_fitness = experiment.baseline_fitness;
    r.candidate_fitness = experiment.candidate_fitness;
    r.confidence = experiment.confidence;
    r.state = AdoptionState::Pending;
    r.revision = next_revision_++;
    return true;
}

bool EvolutionAdoptionJournal::commit(const std::string& id, std::string reason) {
    std::lock_guard lock(mutex_);
    auto it = records_.find(id);
    if (it == records_.end()) return false;
    if (it->second.state == AdoptionState::Adopted) return true;
    if (it->second.state != AdoptionState::Pending) return false;
    it->second.state = AdoptionState::Adopted;
    it->second.reason = std::move(reason);
    it->second.revision = next_revision_++;
    return true;
}

bool EvolutionAdoptionJournal::reject(const std::string& id, std::string reason) {
    std::lock_guard lock(mutex_);
    auto it = records_.find(id);
    if (it == records_.end()) return false;
    if (it->second.state == AdoptionState::Rejected) return true;
    if (it->second.state != AdoptionState::Pending) return false;
    it->second.state = AdoptionState::Rejected;
    it->second.reason = std::move(reason);
    it->second.revision = next_revision_++;
    return true;
}

bool EvolutionAdoptionJournal::rollback(const std::string& id, std::string reason) {
    std::lock_guard lock(mutex_);
    auto it = records_.find(id);
    if (it == records_.end()) return false;
    if (it->second.state == AdoptionState::RolledBack) return true;
    if (it->second.state != AdoptionState::Adopted) return false;
    it->second.state = AdoptionState::RolledBack;
    it->second.reason = std::move(reason);
    it->second.revision = next_revision_++;
    return true;
}

std::optional<AdoptionRecord> EvolutionAdoptionJournal::get(const std::string& id) const {
    std::lock_guard lock(mutex_);
    auto it = records_.find(id);
    if (it == records_.end()) return std::nullopt;
    return it->second;
}

std::vector<AdoptionRecord> EvolutionAdoptionJournal::records() const {
    std::lock_guard lock(mutex_);
    std::vector<AdoptionRecord> out;
    out.reserve(records_.size());
    for (const auto& [_, r] : records_) out.push_back(r);
    return out;
}

} // namespace jarvis::core
