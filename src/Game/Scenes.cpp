#include "scenes.h"

#include "Game/Resources/Materials.h"
#include "Game/Resources/Models.h"

namespace labeeri {

Ref<Scene> testScene() {
    auto scene = makeRef<Scene>();

    {  // Ground
        auto ground = Entity::Create(*scene->ecs());

        ground.getComponent<Transform>(*scene->ecs())->setScale(glm::vec3(50.0));

        auto model = ground.addComponent<Model>(Model(Resources<ModelResource>::Get("basicPlane")), *scene->ecs());
    }

    {  // Lights
        auto sun = Entities::DirectionalLight(*scene, glm::vec3(glm::radians(-110.0), glm::radians(30.0), 0), 0.8f);
    }

    {  // Water
        auto water = Entity::Create(*scene->ecs());

        auto transform = water.getComponent<Transform>(*scene->ecs());
        transform->setPosition(glm::vec3(0.0f, 0.45f, 0.0f));
        transform->setScale(glm::vec3(8.0f));

        water.addComponent<Model>(Model(waterModel()), *scene->ecs());
    }

    {  // Sphere
        auto sphere = Entity::Create(*scene->ecs());

        auto transform = sphere.getComponent<Transform>(*scene->ecs());
        transform->setPosition(glm::vec3(1.0, 1.0, -2.2));

        auto model = sphere.addComponent<Model>(Model(Resources<ModelResource>::Get("basicSphere")), *scene->ecs());
    }

    {  //  Cube
        auto cube = Entity::Create(*scene->ecs());

        auto transform = cube.getComponent<Transform>(*scene->ecs());
        transform->setPosition(glm::vec3(-1.0, 1.5, -2));

        auto model = cube.addComponent<Model>(Model(Resources<ModelResource>::Get("basicCube")), *scene->ecs());

        cube.addComponent<RigidBody>(RigidBody(), *scene->ecs());
        cube.addComponent<Collider>(Collider::AABB(), *scene->ecs());
    }

    {  // Player
        auto player = Entities::Player(*scene);
        player.getComponent<Transform>(*scene->ecs())->move(glm::vec3(0.0, 0.0, 0.0));
    }

    scene->m_renderParameters.skybox = Resources<TextureResource>::Get("the_sky_is_on_fire");

    return scene;
}

}  // namespace labeeri
