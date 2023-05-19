#include "scenes.h"

#include "Game/Resources/Materials.h"
#include "Game/Resources/Models.h"

using namespace labeeri::Engine;

namespace labeeri {

std::shared_ptr<Scene> defaultScene() {
    auto normalTestmaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("grey"));
    normalTestmaterial->m_normalMap = Resources<TextureResource>::Get("normal_test.png");

    auto brickWallMaterial = clone(normalTestmaterial);
    brickWallMaterial->m_diffuseMap = Resources<TextureResource>::Get("brickwall.jpg");
    brickWallMaterial->m_normalMap = Resources<TextureResource>::Get("brickwall_normal.jpg");

    auto catMaterial = clone(normalTestmaterial);
    catMaterial->m_diffuseMap = Resources<TextureResource>::Get("resources/labeeri/textures/catguy.jpg");
    catMaterial->m_normalMap = nullptr;
    catMaterial->m_specular = glm::vec3(0.6f);
    catMaterial->m_shininess = 128.0;

    auto reflectiveMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("grey"));
    reflectiveMaterial->m_diffuse = glm::vec3(0.8, 0.1, 0.1);
    reflectiveMaterial->m_specular = glm::vec3(0.8f);
    reflectiveMaterial->m_metallic = 0.0f;

    auto perlinMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("grey"));
    perlinMaterial->m_diffuse = glm::vec3(0.8f, 1.0f, 0.8f);
    perlinMaterial->m_metallicMap = Resources<TextureResource>::Get("resources/labeeri/textures/perlin512_lin.png");
    perlinMaterial->m_shininess = 128.0;

    auto scene = makeRef<Scene>();

    {  // Ground
        auto ground = Entity::Create(*scene->ecs());

        ground.getComponent<Transform>(*scene->ecs()).setScale(glm::vec3(50.0));

        auto& model = ground.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicPlane"))), *scene->ecs());
        model.m_ref->m_material = normalTestmaterial;
    }

    {  // Lights
        auto sun = Entities::DirectionalLight(*scene, glm::vec3(glm::radians(-110.0), glm::radians(30.0), 0), 0.05f);

        auto pointLight = Entities::PointLight(*scene, glm::vec3(0.0, 4.0, -4.0), 2.0f);
        pointLight.getComponent<Light>(*scene->ecs()).m_properties.diffuse = glm::vec3(1.0, 0.8, 0.8);

        auto spotLight = Entities::SpotLight(*scene, glm::vec3(2.1, 3.5, 1.6), glm::vec3(glm::radians(-50.0), glm::radians(45.0), 0), 1.5f);
        spotLight.getComponent<Light>(*scene->ecs()).m_properties.diffuse = glm::vec3(0.6, 0.6, 1.0);
    }

    {  // Water
        auto water = Entity::Create(*scene->ecs());

        auto& transform = water.getComponent<Transform>(*scene->ecs());
        transform.setPosition(glm::vec3(0.0f, 0.45f, 0.0f));
        transform.setScale(glm::vec3(8.0f));

        water.addComponent<Model>(Model(waterModel()), *scene->ecs());
    }

    {  // Sphere
        auto sphere = Entity::Create(*scene->ecs());

        auto& transform = sphere.getComponent<Transform>(*scene->ecs());
        transform.setPosition(glm::vec3(1.0, 1.0, -2.2));

        auto& model = sphere.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicSphere"))), *scene->ecs());
        model.m_ref->m_material = brickWallMaterial;

        /*
        sphere->m_onUpdate = [](Entity& self, double deltaTime) {
            self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.5, 0) * (float)deltaTime);
            self.transform()->rotate(glm::vec3(0, glm::radians(-15.0f), 0) * (float)deltaTime);
        };
        */
    }

    {  //  Cube
        auto cube = Entity::Create(*scene->ecs());

        auto& transform = cube.getComponent<Transform>(*scene->ecs());
        transform.setPosition(glm::vec3(-1.0, 1.5, -2));

        auto& model = cube.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicCube"))), *scene->ecs());
        model.m_ref->m_material = catMaterial;

        /*
        cube->m_onUpdate = [](Entity& self, double deltaTime) {
            self.transform()->move(glm::vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.15, 0) * (float)deltaTime);
            self.transform()->rotate(glm::vec3(0, glm::radians(20.0f), 0) * (float)deltaTime);
        };
        */
    }

    {  // Reflective teapot
        auto cube = Entity::Create(*scene->ecs());

        auto& transform = cube.getComponent<Transform>(*scene->ecs());
        transform.setPosition(glm::vec3(2, 1, -1));

        cube.addComponent<Model>(Model(makeRef<ModelResource>(reflectiveMaterial, Resources<MeshResource>::Get("teapot.obj"))), *scene->ecs());
    }

    {  // Perlin metallic teapot
        auto cube = Entity::Create(*scene->ecs());

        auto& transform = cube.getComponent<Transform>(*scene->ecs());
        transform.setPosition(glm::vec3(-1.0f, 0.5f, 0.0f));

        cube.addComponent<Model>(Model(makeRef<ModelResource>(perlinMaterial, Resources<MeshResource>::Get("teapot.obj"))), *scene->ecs());
    }

    /*
    auto dragon = Entity::Create();
    dragon->transform()->setPosition(glm::vec3(1.0f, 1.5f, 0.0f));
    dragon->m_model = makeRef<ModelResource>(perlinMaterial, Resources<MeshResource>::Get("xyzrgb_dragon.obj"));
    dragon->m_model->m_material = perlinMaterial;
    scene->addEntity(dragon);
    */

    scene->m_renderParameters.skybox = Resources<TextureResource>::Get("the_sky_is_on_fire");

    return scene;
}

}  // namespace labeeri
