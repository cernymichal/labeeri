#include "scenes.h"

using namespace labeeri::Engine;

namespace labeeri {

std::shared_ptr<Scene> labeeri::defaultScene() {
    auto scene = std::make_shared<Scene>();

    auto material = copyShared(Materials::grey());
    material->m_diffuseMap = loadTexture("resources/labeeri/textures/catguy.jpg");
    material->m_specular = glm::vec3(0.6);
    material->m_shininess = 128.0;

    auto sphere = std::make_shared<Entity>();
    sphere->transform()->setPosition(glm::vec3(1.0, -1.2, -2.2));
    sphere->m_model = copyShared(Models::basicSphere());
    sphere->m_model->m_material = material;
    sphere->m_onUpdate = [](Entity& self, double deltaTime) {
        self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.5f, 0) * (float)deltaTime);
        self.transform()->rotate(glm::vec3(0, glm::radians(-15.0f), 0) * (float)deltaTime);
    };
    scene->addEntity(sphere);

    auto cube = std::make_shared<Entity>();
    cube->transform()->setPosition(glm::vec3(-1.0, 0, -2));
    cube->m_model = copyShared(Models::basicCube());
    cube->m_model->m_material = material;
    cube->m_onUpdate = [](Entity& self, double deltaTime) {
        self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.15f, 0) * (float)deltaTime);
        self.transform()->rotate(glm::vec3(0, glm::radians(20.0f), 0) * (float)deltaTime);
    };
    scene->addEntity(cube);

    cube = std::make_shared<Entity>();
    cube->transform()->setPosition(glm::vec3(5.0, 5.0, -5.0));
    cube->transform()->setScale(glm::vec3(.1));
    cube->m_model = copyShared(Models::basicCube());
    cube->m_model->m_material = Materials::flatGrey();
    scene->addEntity(cube);

    return scene;
}

}  // namespace labeeri
