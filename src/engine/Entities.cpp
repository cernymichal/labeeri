#include "Entities.h"

namespace labeeri::Engine {

std::shared_ptr<Entity> Entities::Flycam(float speed, double sensitivity) {
    auto entity = std::make_shared<Entity>();

    entity->m_camera = std::make_shared<Camera>(entity->transform());
    entity->m_movement = std::make_shared<Movement>(entity->transform(), speed);
    entity->m_look = std::make_shared<Look>(entity->transform(), sensitivity);

    return entity;
}

}  // namespace labeeri::Engine
