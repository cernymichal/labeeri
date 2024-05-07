#include "scenes.h"

#include "Engine/Entities.h"
#include "Engine/Resources/Resources.h"
#include "Engine/Scene/Components/Components.h"

namespace labeeri::Engine {

Ref<Scene> Scenes::showcase() {
    auto normalTestmaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
    normalTestmaterial->m_normalMap = Resources<TextureResource>::Get("normal_test.png");

    auto brickWallMaterial = clone(normalTestmaterial);
    brickWallMaterial->m_diffuseMap = Resources<TextureResource>::Get("brickwall.jpg");
    brickWallMaterial->m_normalMap = Resources<TextureResource>::Get("brickwall_normal.jpg");

    auto catMaterial = clone(normalTestmaterial);
    catMaterial->m_diffuseMap = Resources<TextureResource>::Get("catguy.jpg");
    catMaterial->m_normalMap = nullptr;
    catMaterial->m_specular = vec3(0.6f);
    catMaterial->m_shininess = 128.0;

    auto reflectiveMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
    reflectiveMaterial->m_diffuse = vec3(0.8, 0.1, 0.1);
    reflectiveMaterial->m_specular = vec3(0.8f);
    reflectiveMaterial->m_metallic = 0.0f;

    auto perlinMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
    perlinMaterial->m_diffuse = vec3(0.8f, 1.0f, 0.8f);
    perlinMaterial->m_metallicMap = Resources<TextureResource>::Get("checkerboard_lin.png");
    perlinMaterial->m_shininess = 128.0;

    auto scene = makeRef<Scene>();

    {  // Ground
        auto ground = Entity::Create(scene->ecs());

        ground.getComponent<Transform>(scene->ecs())->setScale(vec3(50.0));

        auto model = ground.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicPlane"))), scene->ecs());
        model->m_ref->m_material = normalTestmaterial;
    }

    {  // Lights
        auto sun = Entities::DirectionalLight(scene, vec3(glm::radians(-110.0), glm::radians(30.0), 0), 0.05f);

        auto pointLight = Entities::PointLight(scene, vec3(0.0, 4.0, -4.0), 2.0f);
        pointLight.getComponent<Light>(scene->ecs())->m_properties.diffuse = vec3(1.0, 0.8, 0.8);

        auto spotLight = Entities::SpotLight(scene, vec3(2.1, 3.5, 1.6), vec3(glm::radians(-50.0), glm::radians(45.0), 0), 1.5f);
        spotLight.getComponent<Light>(scene->ecs())->m_properties.diffuse = vec3(0.6, 0.6, 1.0);
    }

    {  // Sphere
        auto sphere = Entity::Create(scene->ecs());

        auto transform = sphere.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(1.0, 1.0, -2.2));

        auto model = sphere.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicSphere"))), scene->ecs());
        model->m_ref->m_material = brickWallMaterial;

        /*
        sphere->m_onUpdate = [](Entity& self, f64 deltaTime) {
            self.transform()->move(vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.5, 0) * (f32)deltaTime);
            self.transform()->rotate(vec3(0, glm::radians(-15.0f), 0) * (f32)deltaTime);
        };
        */
    }

    {  //  Cube
        auto cube = Entity::Create(scene->ecs());

        auto transform = cube.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(-1.0, 1.5, -2));

        auto model = cube.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicCube"))), scene->ecs());
        model->m_ref->m_material = catMaterial;

        cube.addComponent<RigidBody>(RigidBody(), scene->ecs());
        cube.addComponent<Collider>(Collider::AABB(), scene->ecs());

        /*
        cube->m_onUpdate = [](Entity& self, f64 deltaTime) {
            self.transform()->move(vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * 0.15, 0) * (f32)deltaTime);
            self.transform()->rotate(vec3(0, glm::radians(20.0f), 0) * (f32)deltaTime);
        };
        */
    }

    {  // Reflective teapot
        auto teapot = Entity::Create(scene->ecs());

        auto transform = teapot.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(2, 1, -1));

        teapot.addComponent<Model>(Model(makeRef<ModelResource>(reflectiveMaterial, Resources<MeshResource>::Get("teapot.obj"))), scene->ecs());
    }

    {  // Perlin metallic teapot
        auto teapot = Entity::Create(scene->ecs());

        auto transform = teapot.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(-1.0f, 0.5f, 0.0f));

        teapot.addComponent<Model>(Model(makeRef<ModelResource>(perlinMaterial, Resources<MeshResource>::Get("teapot.obj"))), scene->ecs());
    }

    {  // Perlin metallic dragon
        auto dragon = Entity::Create(scene->ecs());

        auto transform = dragon.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(1.0f, 1.5f, 0.0f));

        dragon.addComponent<Model>(Model(makeRef<ModelResource>(clone(reflectiveMaterial), Resources<MeshResource>::Get("xyzrgb_dragon.obj"))), scene->ecs());
    }

    {  // Flycam
        auto flycam = Entities::Flycam(scene);
        flycam.getComponent<Transform>(scene->ecs())->move(vec3(0.0, 2.5, 0.0));
    }

    scene->m_renderParameters.skybox = Resources<TextureResource>::Get("syferfontein_18d");

    return scene;
}

}  // namespace labeeri::Engine
