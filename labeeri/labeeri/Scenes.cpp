#include "Scenes.h"

#include "Application.h"
#include "Entities.h"
#include "Resources/Load.h"
#include "Resources/Resources.h"
#include "Scene/Components/Components.h"

namespace labeeri {

void Scenes::loadDefaultResources() {
    Resources<MaterialResource>::Set("flatWhite") = makeRef<FlatMaterialResource>(Resources<ShaderResource>::Get("shaders/flat"), vec3(1.0f));
    Resources<MaterialResource>::Set("gray") = makeRef<ShadedMaterialResource>(Resources<ShaderResource>::Get("shaders/phong"), vec3(0.7f));
    Resources<MaterialResource>::Set("UVTest") = makeRef<FlatMaterialResource>(Resources<ShaderResource>::Get("shaders/flat"), Resources<TextureResource>::Get("textures/uv_test.png"));

    Resources<ModelResource>::Set("whiteCube") = makeRef<ModelResource>(Resources<MaterialResource>::Get("flatWhite"), Resources<MeshResource>::Get("models/cube.obj"));
    Resources<ModelResource>::Set("whiteSphere") = makeRef<ModelResource>(Resources<MaterialResource>::Get("flatWhite"), Resources<MeshResource>::Get("models/sphere.obj"));
    Resources<ModelResource>::Set("whiteCone") = makeRef<ModelResource>(Resources<MaterialResource>::Get("flatWhite"), Resources<MeshResource>::Get("models/cone.obj"));
    Resources<ModelResource>::Set("basicCube") = makeRef<ModelResource>(Resources<MaterialResource>::Get("gray"), Resources<MeshResource>::Get("models/cube.obj"));
    Resources<ModelResource>::Set("basicSphere") = makeRef<ModelResource>(Resources<MaterialResource>::Get("gray"), Resources<MeshResource>::Get("models/sphere.obj"));
    Resources<ModelResource>::Set("basicPlane") = makeRef<ModelResource>(Resources<MaterialResource>::Get("gray"), Resources<MeshResource>::Get("models/plane.obj"));
    Resources<ModelResource>::Set("basicCone") = makeRef<ModelResource>(Resources<MaterialResource>::Get("gray"), Resources<MeshResource>::Get("models/cone.obj"));
}

Ref<Scene> Scenes::showcase() {
    loadDefaultResources();

    auto normalTestmaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
    normalTestmaterial->m_normalMap = Resources<TextureResource>::Get("textures/normal_test.png");

    auto brickWallMaterial = clone(normalTestmaterial);
    brickWallMaterial->m_diffuseMap = Resources<TextureResource>::Get("textures/brickwall.jpg");
    brickWallMaterial->m_normalMap = Resources<TextureResource>::Get("textures/brickwall_normal.jpg");

    auto catMaterial = clone(normalTestmaterial);
    catMaterial->m_diffuseMap = Resources<TextureResource>::Get("textures/catguy.jpg");
    catMaterial->m_normalMap = nullptr;
    catMaterial->m_specular = vec3(0.6f);
    catMaterial->m_shininess = 128.0;

    auto reflectiveMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
    reflectiveMaterial->m_diffuse = vec3(0.8, 0.1, 0.1);
    reflectiveMaterial->m_specular = vec3(0.8f);
    reflectiveMaterial->m_metallic = 0.0f;

    auto perlinMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
    perlinMaterial->m_diffuse = vec3(0.8f, 1.0f, 0.8f);
    perlinMaterial->m_metallicMap = Resources<TextureResource>::Get("textures/checkerboard_lin.png");
    perlinMaterial->m_shininess = 128.0;

    auto scene = makeRef<Scene>();
    LAB_APP.setScene(scene);

    {  // Ground
        auto ground = Entity::Create(scene->ecs());

        ground.getComponent<Transform>(scene->ecs())->setScale(vec3(50.0));

        auto model = ground.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicPlane"))), scene->ecs());
        model->m_ref->m_material = catMaterial;
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
    }

    {  //  Cube
        auto cube = Entity::Create(scene->ecs());

        auto transform = cube.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(-1.0, 1.5, -2));

        auto model = cube.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicCube"))), scene->ecs());
        model->m_ref->m_material = normalTestmaterial;

        cube.addComponent<RigidBody>(RigidBody(), scene->ecs());
        cube.addComponent<Collider>(Collider::AABB(), scene->ecs());
    }

    {  // Reflective teapot
        auto teapot = Entity::Create(scene->ecs());

        auto transform = teapot.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(2, 1, -1));

        teapot.addComponent<Model>(Model(makeRef<ModelResource>(reflectiveMaterial, Resources<MeshResource>::Get("models/teapot.obj"))), scene->ecs());
    }

    {  // Perlin metallic teapot
        auto teapot = Entity::Create(scene->ecs());

        auto transform = teapot.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(-1.0f, 0.5f, 0.0f));

        teapot.addComponent<Model>(Model(makeRef<ModelResource>(perlinMaterial, Resources<MeshResource>::Get("models/teapot.obj"))), scene->ecs());
    }

    {  // Perlin metallic dragon
        auto dragon = Entity::Create(scene->ecs());

        auto transform = dragon.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(1.0f, 1.5f, 0.0f));

        dragon.addComponent<Model>(Model(makeRef<ModelResource>(clone(reflectiveMaterial), Resources<MeshResource>::Get("models/xyzrgb_dragon.obj"))), scene->ecs());
    }

    {  // Flycam
        auto flycam = Entities::Flycam(scene);
        flycam.getComponent<Transform>(scene->ecs())->move(vec3(0.0, 2.5, 0.0));
    }

    scene->m_renderParameters.skybox = loadCubemap("textures/cubemaps/syferfontein_18d");

    return scene;
}

}  // namespace labeeri
