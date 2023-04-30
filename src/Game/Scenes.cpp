#include "scenes.h"

using namespace labeeri::Engine;

namespace labeeri {

std::shared_ptr<Scene> labeeri::defaultScene() {
    auto scene = std::make_shared<Scene>();

    auto material = copyShared(Materials::UVTest());
    material->m_texture = loadTexture("resources/labeeri/textures/catguy.jpg");

    auto sphere = std::make_shared<Entity>();
    sphere->transform()->setPosition(glm::vec3(1.0, -1.2, -2.2));
    sphere->m_model = copyShared(Models::basicSphere());
    sphere->m_model->m_material = material;
    sphere->m_onUpdate = [](Entity& self, double deltaTime) {
        self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.01f, 0));
        self.transform()->rotate(glm::vec3(0, glm::radians(-15.0f), 0) * (float)deltaTime);
    };
    scene->addEntity(sphere);

    auto cube = std::make_shared<Entity>();
    cube->transform()->setPosition(glm::vec3(-1.0, 0, -2));
    cube->m_model = copyShared(Models::basicCube());
    cube->m_model->m_material = material;
    cube->m_onUpdate = [](Entity& self, double deltaTime) {
        self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.002f, 0));
        self.transform()->rotate(glm::vec3(0, glm::radians(20.0f), 0) * (float)deltaTime);
    };
    scene->addEntity(cube);

    return scene;
}

}  // namespace labeeri
