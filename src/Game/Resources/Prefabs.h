#pragma once

#include "Engine/API.h"

namespace labeeri {

/**
 * @brief Create the copied room entity. Together with its contents.
 *
 * @param scene The scene to create the room in.
 * @param offset The offset of the room.
 * @param setpiece The setpiece to use for the room.
 * @return The room entity.
 */
Entity roomPrefab(const Ref<Scene>& scene, vec2 offset = vec2(0.0f), Entity setpiece = NULL_ENTITY);

}  // namespace labeeri
