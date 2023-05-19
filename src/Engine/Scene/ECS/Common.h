#pragma once

namespace labeeri::Engine {

using EntityId = uint32_t;
inline constexpr EntityId NULL_ENTITY = -1;

namespace ECS {

using ComponentType = uint8_t;
using ComponentSignature = std::bitset<MAX_COMPONENTS>;

}  // namespace ECS

}  // namespace labeeri::Engine
