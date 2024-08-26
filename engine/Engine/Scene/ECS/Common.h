#pragma once

namespace labeeri::Engine {

using EntityId = u32;
inline constexpr EntityId NULL_ENTITY = -1;

namespace ECS {

/*
 * @brief The id of a component type.
 */
using ComponentType = u8;

/*
 * @brief The signature of an entity - what components it has.
 */
using ComponentSignature = std::bitset<MAX_COMPONENTS>;

}  // namespace ECS

}  // namespace labeeri::Engine
