#include "scenes.h"

#include "Game/Resources/Materials.h"
#include "Game/Resources/Models.h"

using namespace labeeri::Engine;

namespace labeeri {

std::shared_ptr<Scene> defaultScene() {
    auto scene = std::make_shared<Scene>();

    auto normalTestmaterial = cloneAs<ShadedMaterial>(Resources<Material>::get("grey"));
    normalTestmaterial->m_normalMap = Resources<Texture>::get("normal_test.png");

    auto brickWallMaterial = clone(normalTestmaterial);
    brickWallMaterial->m_diffuseMap = Resources<Texture>::get("brickwall.jpg");
    brickWallMaterial->m_normalMap = Resources<Texture>::get("brickwall_normal.jpg");

    auto catMaterial = clone(normalTestmaterial);
    catMaterial->m_diffuseMap = Resources<Texture>::get("resources/labeeri/textures/catguy.jpg");
    catMaterial->m_normalMap = nullptr;
    catMaterial->m_specular = glm::vec3(0.6f);
    catMaterial->m_shininess = 128.0;

    auto ground = Entity::Create();
    ground->transform()->setScale(glm::vec3(50.0));
    ground->m_model = clone(Resources<Model>::get("basicPlane"));
    ground->m_model->m_material = normalTestmaterial;
    scene->addEntity(ground);

    auto sun = Entities::DirectionalLight(glm::vec3(glm::radians(-110.0), glm::radians(30.0), 0), 0.05f);
    auto pointLight = Entities::PointLight(glm::vec3(0.0, 4.0, -4.0), 2.0f);
    pointLight->m_light->m_properties.diffuse = glm::vec3(1.0, 0.8, 0.8);
    auto spotLight = Entities::SpotLight(glm::vec3(2.1, 3.5, 1.6), glm::vec3(glm::radians(-50.0), glm::radians(45.0), 0), 1.5f);
    spotLight[0]->m_light->m_properties.diffuse = glm::vec3(0.6, 0.6, 1.0);

    scene->addEntity(sun);
    scene->addEntity(pointLight);
    scene->addEntity(spotLight);

    auto water = Entity::Create();
    water->transform()->setPosition(glm::vec3(0.0f, 0.45f, 0.0f));
    water->transform()->setScale(glm::vec3(8.0f));
    water->m_model = waterModel();
    scene->addEntity(water);

    water = Entity::Create();
    water->transform()->setPosition(glm::vec3(-32.0f, 0.45f, 0.0f));
    water->transform()->setScale(glm::vec3(8.0f));
    water->m_model = waterModel();
    scene->addEntity(water);

    water = Entity::Create();
    water->transform()->setPosition(glm::vec3(0.0f, 0.45f, -32.0f));
    water->transform()->setScale(glm::vec3(8.0f));
    water->m_model = waterModel();
    scene->addEntity(water);

    water = Entity::Create();
    water->transform()->setPosition(glm::vec3(-32.0f, 0.45f, -32.0f));
    water->transform()->setScale(glm::vec3(8.0f));
    water->m_model = waterModel();
    scene->addEntity(water);


    auto sphere = Entity::Create();
    sphere->transform()->setPosition(glm::vec3(1.0, 1.0, -2.2));
    sphere->m_model = clone(Resources<Model>::get("basicSphere"));
    sphere->m_model->m_material = brickWallMaterial;
    sphere->m_onUpdate = [](Entity& self, double deltaTime) {
        self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.5, 0) * (float)deltaTime);
        self.transform()->rotate(glm::vec3(0, glm::radians(-15.0f), 0) * (float)deltaTime);
    };
    scene->addEntity(sphere);

    auto cube = Entity::Create();
    cube->transform()->setPosition(glm::vec3(-1.0, 1.5, -2));
    cube->m_model = clone(Resources<Model>::get("basicCube"));
    cube->m_model->m_material = catMaterial;
    cube->m_onUpdate = [](Entity& self, double deltaTime) {
        self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.15, 0) * (float)deltaTime);
        self.transform()->rotate(glm::vec3(0, glm::radians(20.0f), 0) * (float)deltaTime);
    };
    scene->addEntity(cube);

    auto reflectiveMaterial = cloneAs<ShadedMaterial>(Resources<Material>::get("grey"));
    reflectiveMaterial->m_diffuse = glm::vec3(0.8, 0.1, 0.1);
    reflectiveMaterial->m_specular = glm::vec3(0.8f);
    reflectiveMaterial->m_metallic = 0.0f;

    auto reflectiveCube = Entity::Create();
    reflectiveCube->transform()->setPosition(glm::vec3(2, 1, -1));
    reflectiveCube->m_model = makeRef<Model>(reflectiveMaterial, Resources<Mesh>::get("teapot.obj"));
    scene->addEntity(reflectiveCube);

    auto perlinMaterial = cloneAs<ShadedMaterial>(Resources<Material>::get("grey"));
    perlinMaterial->m_diffuse = glm::vec3(0.8f, 1.0f, 0.8f);
    perlinMaterial->m_metallicMap = Resources<Texture>::get("resources/labeeri/textures/perlin512_lin.png");
    perlinMaterial->m_shininess = 128.0;

    auto teapot = Entity::Create();
    teapot->transform()->setPosition(glm::vec3(-1.0f, 0.5f, 0.0f));
    teapot->m_model = makeRef<Model>(perlinMaterial, Resources<Mesh>::get("teapot.obj"));
    scene->addEntity(teapot);

    /*
    auto dragon = Entity::Create();
    dragon->transform()->setPosition(glm::vec3(1.0f, 1.5f, 0.0f));
    dragon->m_model = makeRef<Model>(perlinMaterial, Resources<Mesh>::get("xyzrgb_dragon.obj"));
    dragon->m_model->m_material = perlinMaterial;
    scene->addEntity(dragon);
    */

    scene->m_renderParameters.skybox = Resources<Texture>::get("the_sky_is_on_fire");

    return scene;
}

}  // namespace labeeri
