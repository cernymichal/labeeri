#include "scenes.h"

#include "Game/Resources/Materials.h"
#include "Game/Resources/Models.h"
#include "Game/Resources/Prefabs.h"
#include "Game/Resources/Scripts/BloodyFaceInteraction.h"
#include "Game/Resources/Scripts/CameraSwitcher.h"
#include "Game/Resources/Scripts/FlashlightController.h"
#include "Game/Resources/Scripts/FloatingMovement.h"
#include "Game/Resources/Scripts/LightBlinking.h"
#include "Game/Resources/Scripts/LightSwitchInteraction.h"
#include "Game/Resources/Scripts/MaxwellInteraction.h"
#include "Game/Resources/Scripts/RotatingMovement.h"

namespace labeeri {

Ref<Scene> testScene() {
    auto scene = makeRef<Scene>();

    {  // Ground
        auto ground = Entity::Create(scene->ecs());

        ground.getComponent<Transform>(scene->ecs())->setScale(vec3(10.0));

        auto model = ground.addComponent<Model>(Model(Resources<ModelResource>::Get("basicPlane")), scene->ecs());
    }

    {  // Lights
        auto sun = Entities::DirectionalLight(scene, vec3(glm::radians(-110.0), glm::radians(30.0), 0), 0.8f);
    }

    {  // Water
        auto water = Entity::Create(scene->ecs());

        auto transform = water.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(0.0f, 0.45f, 0.0f));
        transform->setScale(vec3(8.0f));

        water.addComponent<Model>(Model(waterModel()), scene->ecs());
    }

    {  // Sphere
        auto sphere = Entity::Create(scene->ecs());

        auto transform = sphere.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(1.0, 1.0, -2.2));

        auto model = sphere.addComponent<Model>(Model(Resources<ModelResource>::Get("basicSphere")), scene->ecs());
    }

    {  //  Cube
        auto cube = Entity::Create(scene->ecs());

        auto transform = cube.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(-1.0, 1.5, -2));

        auto model = cube.addComponent<Model>(Model(Resources<ModelResource>::Get("basicCube")), scene->ecs());

        cube.addComponent<RigidBody>(RigidBody(), scene->ecs());
        cube.addComponent<Collider>(Collider::AABB(), scene->ecs());
    }

    {  // Player
        auto player = Entities::Player(scene);
        player.getComponent<Transform>(scene->ecs())->move(vec3(0.0, 0.0, 0.0));
    }

    scene->m_renderParameters.skybox = Resources<TextureResource>::Get("the_sky_is_on_fire");

    return scene;
}

Ref<Scene> loadLabyrinthScene() {
    auto scene = makeRef<Scene>();
    LAB_APP.setScene(scene);

    Entity player;
    std::vector<Entity> cameras;

    {  // Player
        player = Entities::Player(scene);
        player.getComponent<Transform>(scene->ecs())->move(vec3(0.0f, 0.0f, 2.0f));
        player.addComponent<Light>(Light::Spot(LightProperties(vec3(0.0f), vec3(2.0f), vec3(1.0f))), scene->ecs())
            ->m_intensity = 0.0f;

        scene->addScript<FlashlightController>(player);
    }

    {  // Lights
        auto sun = Entities::DirectionalLight(scene, vec3(glm::radians(-110.0), glm::radians(30.0), 0), 0.05f);
        sun.getComponent<Transform>()->move(vec3(0.0f, -2.0f, 0.0f));
    }

    {  // Rooms
        i32 axisCount = 5;
        f32 roomSize = 10.0f;
        for (f32 x = -(axisCount - 1) * roomSize / 2.0f; x <= (axisCount - 1) * roomSize / 2.0f; x += roomSize) {
            for (f32 z = -(axisCount - 1) * roomSize / 2.0f; z <= (axisCount - 1) * roomSize / 2.0f; z += roomSize)
                roomPrefab(scene, vec2(x, z));
        }
    }

    {  // Light
        std::array<Entity, 5> lights = {
            Entities::PointLight(scene, vec3(0.0f, 3.0f, 0.0f), 1.8f),
            Entities::PointLight(scene, vec3(10.0f, 3.0f, 0.0f), 1.2f),
            Entities::PointLight(scene, vec3(0.0f, 3.0f, 10.0f), 1.2f),
            Entities::PointLight(scene, vec3(-10.0f, 3.0f, 0.0f), 1.2f),
            Entities::PointLight(scene, vec3(0.0f, 3.0f, -10.0f), 1.2f)};

        for (Entity light : lights)
            scene->addScript<LightSwitchInteraction>(light);

        scene->addScript<LightBlinking>(lights[4]);
    }

    {  // Water
        i32 axisCount = 2;
        f32 tileSize = 25.0f;
        for (f32 x = -(axisCount - 1) * tileSize / 2.0f; x <= (axisCount - 1) * tileSize / 2.0f; x += tileSize) {
            for (f32 z = -(axisCount - 1) * tileSize / 2.0f; z <= (axisCount - 1) * tileSize / 2.0f; z += tileSize) {
                auto water = Entity::Create(scene->ecs());

                auto transform = water.getComponent<Transform>(scene->ecs());
                transform->setPosition(vec3(x, 0.02f, z));
                transform->setScale(vec3(12.5f / 2, 3.0f, 12.5f / 2));

                water.addComponent<Model>(Model(waterModel()), scene->ecs());
            }
        }
    }

    {  // Sphere system
        auto sphereAMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        sphereAMaterial->m_diffuseMap = Resources<TextureResource>::Get("resources/labeeri/textures/slab_tiles/diffuse.png");
        sphereAMaterial->m_specular = vec3(0.4f);
        sphereAMaterial->m_normalMap = Resources<TextureResource>::Get("resources/labeeri/textures/slab_tiles/normal.hdr");

        auto sphereBMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        sphereBMaterial->m_diffuse = vec3(1.0f);
        sphereBMaterial->m_specular = vec3(0.7f);
        sphereBMaterial->m_metallic = 0.05f;

        auto sphereCMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        sphereCMaterial->m_diffuse = vec3(0.14f, 0.18f, 0.49f);
        sphereCMaterial->m_specular = vec3(0.7f);

        auto sphereA = Entity::Create(scene->ecs());
        auto transformA = sphereA.getComponent<Transform>(scene->ecs());
        transformA->setPosition(vec3(0.0f, 1.5f, 0.0f));
        transformA->setScale(vec3(0.6f));
        scene->addScript<FloatingMovement>(sphereA, 0.1f);
        scene->addScript<RotatingMovement>(sphereA, quat(vec3(0.0f, glm::radians(0.2f), 0.0f)));
        auto model = sphereA.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicSphere"))), scene->ecs());
        model->m_ref->m_material = sphereAMaterial;

        auto sphereB = Entity::Create(scene->ecs());
        auto transformB = sphereB.getComponent<Transform>(scene->ecs());
        transformB->setPosition(vec3(0.6f, 1.5f, 0.0f));
        transformB->setScale(vec3(0.4f));
        transformB->setParent(sphereA);
        scene->addScript<RotatingMovement>(sphereB, quat(vec3(0.0f, glm::radians(-0.6f), 0.0f)));
        model = sphereB.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicSphere"))), scene->ecs());
        model->m_ref->m_material = sphereBMaterial;

        auto plane = Entity::Create(scene->ecs());
        auto transformPlane = plane.getComponent<Transform>(scene->ecs());
        transformPlane->setPosition(vec3(0.6f, 1.5f, 0.12f));
        transformPlane->setRotation(vec3(glm::radians(90.0f), 0.0f, 0.0f));
        transformPlane->setParent(sphereB);
        plane.addComponent<Model>(Model(makeRef<ModelResource>(makeRef<FlareMaterial>(), Resources<MeshResource>::Get("plane.obj"))), scene->ecs());

        auto sphereCHolder = Entity::Create(scene->ecs());
        auto transformCHolder = sphereCHolder.getComponent<Transform>(scene->ecs());
        transformCHolder->setParent(sphereA);
        *transformCHolder = *transformB;
        scene->addScript<RotatingMovement>(sphereCHolder, quat(vec3(glm::radians(-0.3f), 0.0f, 0.0f)));

        auto sphereC = Entity::Create(scene->ecs());
        auto transformC = sphereC.getComponent<Transform>(scene->ecs());
        transformC->setPosition(vec3(0.6f, 1.8f, 0.0f));
        transformC->setScale(vec3(0.2f));
        transformC->setParent(sphereCHolder);
        model = sphereC.addComponent<Model>(Model(clone(Resources<ModelResource>::Get("basicCube"))), scene->ecs());
        model->m_ref->m_material = sphereCMaterial;
        scene->addScript<RotatingMovement>(sphereC, quat(vec3(0.0f, glm::radians(0.6f), 0.0f)));

        {  // Sphere view
            auto camera = Entity::Create(scene->ecs());

            auto transform = camera.getComponent<Transform>(scene->ecs());
            transform->setPosition(vec3(0.6f, 1.6f, 0.0f));
            transform->setParent(sphereA);

            camera.addComponent<Camera>(Camera(false, 90.0f), scene->ecs());

            cameras.push_back(camera);
        }
    }

    {  // Bottom view
        auto camera = Entity::Create(scene->ecs());

        auto transform = camera.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(4.0f, 0.4f, 4.0f));
        transform->setRotation(glm::radians(vec3(20.0f, 45.0f, 0.0f)));

        camera.addComponent<Camera>(Camera(false, 110.0f), scene->ecs());

        cameras.push_back(camera);
    }

    {  // Bunny
        auto material = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        material->m_diffuse = vec3(0.98f, 1.0f, 0.21f);
        material->m_specular = vec3(1.0f, 0.94f, 0.33f);
        material->m_metallic = 0.55f;

        auto entity = Entity::Create(scene->ecs());

        auto transform = entity.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(10.0f, 0.8f, 0.0f));
        transform->setScale(vec3(1.2f));
        auto model = entity.addComponent<Model>(Model(makeRef<ModelResource>(material, Resources<MeshResource>::Get("bunny.obj"))), scene->ecs());
    }

    {  // Dragon
        auto material = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        material->m_diffuse = vec3(0.1f, 0.56f, 0.29f);
        material->m_specular = vec3(0.70f, 1.0f, 0.0f);
        material->m_metallic = 0.0f;

        auto entity = Entity::Create(scene->ecs());

        auto transform = entity.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(-10.0f, 1.2f, 0.0f));
        transform->setScale(vec3(1.2f));
        auto model = entity.addComponent<Model>(Model(makeRef<ModelResource>(material, Resources<MeshResource>::Get("xyzrgb_dragon.obj"))), scene->ecs());
    }

    {  // Maxwell
        auto material = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        material->m_diffuseMap = Resources<TextureResource>::Get("maxwell.jpg");
        material->m_specular = vec3(0.0f);

        auto entity = Entity::Create(scene->ecs());

        auto transform = entity.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(0.0f, 0.8f, 10.0f));
        transform->rotate(vec3(0.0f, glm::radians(110.0f), 0.0f));
        transform->setScale(vec3(1.0f));
        auto model = entity.addComponent<Model>(Model(makeRef<ModelResource>(material, Resources<MeshResource>::Get("maxwell.obj"))), scene->ecs());

        scene->addScript<MaxwellInteraction>(entity);
    }

    {  // Ball
        auto material = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        material->m_diffuse = vec3(1.0f, 0.0f, 0.0f);
        material->m_specular = vec3(1.0f);
        material->m_metallic = 0.9f;

        auto entity = Entity::Create(scene->ecs());

        auto transform = entity.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(0.0f, 1.3f, -10.0f));
        transform->setScale(vec3(1.0f));
        auto model = entity.addComponent<Model>(Model(makeRef<ModelResource>(material, Resources<MeshResource>::Get("resources/labeeri/models/ball.obj"))), scene->ecs());
    }

    {  // Dynamic ball
        auto material = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        material->m_diffuse = vec3(1.0f);
        material->m_specular = vec3(0.6f);
        material->m_metallic = 0.1f;
        material->m_metallicMap = Resources<TextureResource>::Get("checkerboard_lin.png");

        auto entity = Entity::Create(scene->ecs());

        auto transform = entity.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(10.0f, 1.3f, 10.0f));
        transform->setScale(vec3(1.0f));
        auto model = entity.addComponent<Model>(Model(makeRef<ModelResource>(material, Resources<MeshResource>::Get("resources/labeeri/models/dynamic_ball.obj"))), scene->ecs());
    }

    {  // Head
        auto material = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        material->m_diffuse = vec3(0.8f, 0.61f, 0.48f);
        material->m_specular = vec3(0.5f, 0.52f, 0.41f);
        material->m_shininess = 16.0f;
        material->m_metallic = 0.0f;

        auto entity = Entity::Create(scene->ecs());

        auto transform = entity.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(10.0f, 1.2f, -10.0f));
        transform->setScale(vec3(2.0f));
        auto model = entity.addComponent<Model>(Model(makeRef<ModelResource>(material, Resources<MeshResource>::Get("resources/labeeri/models/head.obj"))), scene->ecs());

        scene->addScript<BloodyFaceInteraction>(entity);
    }

    {  // Knot
        auto material = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        material->m_diffuse = vec3(1.0f);
        material->m_specular = vec3(1.0f);
        material->m_metallic = 1.0f;

        auto entity = Entity::Create(scene->ecs());

        auto transform = entity.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(0.0f, 1.3f, -20.0f));
        transform->setScale(vec3(1.0f));
        auto model = entity.addComponent<Model>(Model(makeRef<ModelResource>(material, Resources<MeshResource>::Get("resources/labeeri/models/knot.obj"))), scene->ecs());
    }

    {  // Knot view
        auto camera = Entity::Create(scene->ecs());

        auto transform = camera.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(0.0f, 2.0f, -25.0f));
        transform->setRotation(glm::radians(vec3(-10.0f, 180.0f, 0.0f)));

        camera.addComponent<Camera>(Camera(false, 30.0f), scene->ecs());

        cameras.push_back(camera);
    }

    scene->addScript<CameraSwitcher>(player, cameras);

    scene->m_renderParameters.skybox = loadCubemap("resources/labeeri/textures/cubemaps/dikhololo_night");
    scene->m_renderParameters.fog.color = vec3(0.08f, 0.07f, 0.06f);
    scene->m_renderParameters.fog.density = 0.07f;
    scene->m_renderParameters.postprocessing.exposure = 0.6f;
    scene->m_renderParameters.postprocessing.gamma = 2.0f;

    return scene;
}

}  // namespace labeeri
