#include "scenes.h"

#include "Engine/WindowLayer/ImGuiWindow/EntityWindow.h"

using namespace labeeri::Engine;

namespace labeeri {

std::shared_ptr<Scene> defaultScene() {
    auto scene = std::make_shared<Scene>();

    auto ground = Entity::Create();
    ground->transform()->setScale(glm::vec3(50.0));
    ground->m_model = Resources<Model>::get("basicPlane");
    scene->addEntity(ground);

    auto sun = Entities::DirectionalLight(glm::vec3(glm::radians(-110.0), glm::radians(30.0), 0), .4f);
    auto pointLight = Entities::PointLight(glm::vec3(0.0, 4.0, -4.0));
    pointLight->m_light->m_properties.diffuse = glm::vec3(1.0, 0.8, 0.8);
    auto spotLight = Entities::SpotLight(glm::vec3(2.1, 3.5, 1.6), glm::vec3(glm::radians(-50.0), glm::radians(45.0), 0));
    spotLight[0]->m_light->m_properties.diffuse = glm::vec3(0.6, 0.6, 1.0);

    scene->addEntity(sun);
    scene->addEntity(pointLight);
    scene->addEntity(spotLight);

    auto material = copyShared(std::dynamic_pointer_cast<ShadedMaterial>(Resources<Material>::get("grey")));
    material->m_diffuseMap = Resources<Texture>::get("resources/labeeri/textures/catguy.jpg");
    material->m_specular = glm::vec3(0.6f);
    material->m_shininess = 128.0;

    auto sphere = Entity::Create();
    sphere->transform()->setPosition(glm::vec3(1.0, 1.0, -2.2));
    sphere->m_model = copyShared(Resources<Model>::get("basicSphere"));
    sphere->m_model->m_material = material;
    sphere->m_onUpdate = [](Entity& self, double deltaTime) {
        self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.5f, 0) * (float)deltaTime);
        self.transform()->rotate(glm::vec3(0, glm::radians(-15.0f), 0) * (float)deltaTime);
    };
    scene->addEntity(sphere);

    auto cube = Entity::Create();
    cube->transform()->setPosition(glm::vec3(-1.0, 1.5, -2));
    cube->m_model = copyShared(Resources<Model>::get("basicCube"));
    cube->m_model->m_material = material;
    cube->m_onUpdate = [](Entity& self, double deltaTime) {
        self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.15f, 0) * (float)deltaTime);
        self.transform()->rotate(glm::vec3(0, glm::radians(20.0f), 0) * (float)deltaTime);
    };
    scene->addEntity(cube);

    auto perlinMaterial = copyShared(std::dynamic_pointer_cast<ShadedMaterial>(Resources<Material>::get("grey")));
    perlinMaterial->m_diffuse = glm::vec3(0.8f, 1.0f, 0.8f);
    perlinMaterial->m_specularMap = Resources<Texture>::get("perlin256.png");
    perlinMaterial->m_shininess = 128.0;

    auto teapot = Entity::Create();
    teapot->transform()->setPosition(glm::vec3(-1.0f, 0.5f, 0.0f));
    teapot->m_model = std::make_shared<Model>(perlinMaterial, Resources<Mesh>::get("teapot.obj"));
    teapot->m_model->m_material = perlinMaterial;
    scene->addEntity(teapot);

    /*
    auto dragon = Entity::Create();
    dragon->transform()->setPosition(glm::vec3(1.0f, 1.5f, 0.0f));
    dragon->m_model = std::make_shared<Model>(perlinMaterial, Resources<Mesh>::get("xyzrgb_dragon"));
    dragon->m_model->m_material = perlinMaterial;
    scene->addEntity(dragon);
    */

    LAB_IMGUI->addWindow(std::make_unique<EntityWindow>(sun));
    LAB_IMGUI->addWindow(std::make_unique<EntityWindow>(spotLight[0]));
    LAB_IMGUI->addWindow(std::make_unique<EntityWindow>(pointLight));
    LAB_IMGUI->addWindow(std::make_unique<EntityWindow>(teapot));

    return scene;
}

}  // namespace labeeri
