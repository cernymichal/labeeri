#include "scenes.h"

namespace labeeri {

std::shared_ptr<engine::Scene> labeeri::defaultScene() {
    auto scene = std::make_shared<engine::Scene>();

    /*
    auto cameraEntity = std::make_shared<engine::Entity>();
    cameraEntity->transform()->setPosition(glm::vec3(3, 3, 3));
    cameraEntity->transform()->setRotation(glm::vec3(0, glm::radians(45.0f), 0));
    cameraEntity->transform()->setRotation(cameraEntity->transform()->rotation() * glm::quat(glm::vec3(glm::radians(-40.0f), 0, 0)));
    scene->addEntity(cameraEntity);
    auto camera = std::make_shared<engine::Camera>(cameraEntity->transform());
    */

    auto sphere = std::make_shared<engine::Entity>();
    sphere->m_model = engine::Models::basicSphere();
    sphere->m_onFixedUpdate = [](engine::Entity& self) {
        self.transform()->setPosition(self.transform()->position() + glm::vec3(0.01, 0, 0));
    };
    scene->addEntity(sphere);

    sphere = std::make_shared<engine::Entity>();
    sphere->m_model = engine::Models::basicSphere();
    sphere->m_onFixedUpdate = [](engine::Entity& self) {
        self.transform()->setPosition(self.transform()->position() + glm::vec3(-0.01, 0, 0));
    };
    scene->addEntity(sphere);

    sphere = std::make_shared<engine::Entity>();
    sphere->m_model = engine::Models::basicSphere();
    sphere->m_onFixedUpdate = [](engine::Entity& self) {
        self.transform()->setPosition(self.transform()->position() + glm::vec3(0, 0.01, 0));
    };
    scene->addEntity(sphere);

    sphere = std::make_shared<engine::Entity>();
    sphere->m_model = engine::Models::basicSphere();
    sphere->m_onFixedUpdate = [](engine::Entity& self) {
        self.transform()->setPosition(self.transform()->position() + glm::vec3(0, -0.01, 0));
    };
    scene->addEntity(sphere);

    sphere = std::make_shared<engine::Entity>();
    sphere->m_model = engine::Models::basicSphere();
    sphere->m_onFixedUpdate = [](engine::Entity& self) {
        self.transform()->setPosition(self.transform()->position() + glm::vec3(0, 0, 0.01));
    };
    scene->addEntity(sphere);

    sphere = std::make_shared<engine::Entity>();
    sphere->m_model = engine::Models::basicSphere();
    sphere->m_onFixedUpdate = [](engine::Entity& self) {
        self.transform()->setPosition(self.transform()->position() + glm::vec3(0, 0, -0.01));
    };
    scene->addEntity(sphere);

    return scene;
}

}  // namespace labeeri
