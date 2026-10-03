#include "jarvis/core/memory.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <limits>
#include <mutex>
#include <utility>

namespace jarvis::core {
namespace {

constexpr std::uint64_t kMaxSerializedSize = 1ULL << 30;
constexpr std::uint64_t kMaxAttributes = 1ULL << 20;
constexpr std::uint64_t kMetadataMagicV1 = 0x4a41525649534d31ULL; // "JARVISM1"
constexpr std::uint64_t kMetadataMagic = 0x4a41525649534d32ULL; // "JARVISM2"
constexpr std::uint64_t kMaxMetadataRecords = 1ULL << 20;

} // namespace
