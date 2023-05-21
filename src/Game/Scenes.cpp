#include "scenes.h"

#include "Game/Resources/Entities.h"
#include "Game/Resources/Materials.h"
#include "Game/Resources/Models.h"

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

    {  // Lights
        auto sun = Entities::DirectionalLight(scene, vec3(glm::radians(-110.0), glm::radians(30.0), 0), 0.8f);
    }

    {  // Rooms
        int axisCount = 5;
        float roomSize = 10.0f;
        for (float x = -(axisCount - 1) * roomSize / 2.0f; x <= (axisCount - 1) * roomSize / 2.0f; x += roomSize) {
            for (float z = -(axisCount - 1) * roomSize / 2.0f; z <= (axisCount - 1) * roomSize / 2.0f; z += roomSize)
                roomEntity(scene, vec2(x, z));
        }
    }

    {  // Water
        auto water = Entity::Create(scene->ecs());

        auto transform = water.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(0.0f, 0.45f, 0.0f));
        transform->setScale(vec3(8.0f));

        water.addComponent<Model>(Model(waterModel()), scene->ecs());
    }

    {  // Player
        auto player = Entities::Player(scene);
        player.getComponent<Transform>(scene->ecs())->move(vec3(0.0f, 0.0f, 2.0f));
    }

    scene->m_renderParameters.skybox = Resources<TextureResource>::Get("the_sky_is_on_fire");

    return scene;
}

}  // namespace labeeri
