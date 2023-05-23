#pragma once

namespace labeeri::Engine {

using EntityId = uint32_t;
inline constexpr EntityId NULL_ENTITY = -1;

namespace ECS {

/*
 * @brief The id of a component type.
 */
using ComponentType = uint8_t;

/*
 * @brief The signature of an entity - what components it has.
 */
using ComponentSignature = std::bitset<MAX_COMPONENTS>;

}  // namespace ECS

}  // namespace labeeri::Engine
