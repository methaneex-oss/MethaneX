#include "jarvis/core/brain.hpp"

namespace jarvis::core {
static std::string join_ids_branch(const std::vector<std::string>& ids) { std::string out; for (std::size_t i=0;i<ids.size();++i) { if (i) out.push_back('\x1f'); out += ids[i]; } return out; }
}
