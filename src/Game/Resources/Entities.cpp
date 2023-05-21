#include "Entities.h"

namespace labeeri {

Entity labeeri::roomEntity(const Ref<Scene>& scene, vec2 offset, Entity setpiece) {
    static bool initialized = false;

    if (!initialized) {
        Resources<MaterialResource>::Set("room") = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        Resources<ModelResource>::Set("room") = makeRef<ModelResource>(Resources<MaterialResource>::Get("room"), Resources<MeshResource>::Get("resources/labeeri/models/room.obj"));

        Resources<MaterialResource>::Set("table") = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        Resources<ModelResource>::Set("table") = makeRef<ModelResource>(Resources<MaterialResource>::Get("table"), Resources<MeshResource>::Get("resources/labeeri/models/table.obj"));

        initialized = true;
    }

    auto room = Entity::Create(scene->ecs());
    auto table = Entity::Create(scene->ecs());

    {  // Room
        room.getComponent<Transform>(scene->ecs())->setPosition(vec3(offset.x, 0.0f, offset.y));
        room.addComponent<Model>(Model(Resources<ModelResource>::Get("room")), scene->ecs());
    }

    {  // Colliders
        std::array<Entity, 8> colliders = {
            Entities::ColliderCube(scene, vec3(-4.75f, 1.05f, -2.75f), vec3(0.5f, 2.1f, 3.5f)),
            Entities::ColliderCube(scene, vec3(-4.75f, 1.05f, 2.75f), vec3(0.5f, 2.1f, 3.5f)),
            Entities::ColliderCube(scene, vec3(4.75f, 1.05f, -2.75f), vec3(0.5f, 2.1f, 3.5f)),
            Entities::ColliderCube(scene, vec3(4.75f, 1.05f, 2.75f), vec3(0.5f, 2.1f, 3.5f)),

            Entities::ColliderCube(scene, vec3(-2.75f, 1.05f, -4.75f), vec3(3.5f, 2.1f, 0.5f)),
            Entities::ColliderCube(scene, vec3(-2.75f, 1.05f, 4.75f), vec3(3.5f, 2.1f, 0.5f)),
            Entities::ColliderCube(scene, vec3(2.75f, 1.05f, -4.75f), vec3(3.5f, 2.1f, 0.5f)),
            Entities::ColliderCube(scene, vec3(2.75f, 1.05f, 4.75f), vec3(3.5f, 2.1f, 0.5f)),
        };

        for (auto& collider : colliders) {
            auto transform = collider.getComponent<Transform>(scene->ecs());
            transform->move(vec3(offset.x, 0.0f, offset.y));
            transform->setParent(room);
        }
    }

    {  // Table
        auto transform = table.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(offset.x, 0.0f, offset.y));
        //transform->setParent(room);
        table.addComponent<Model>(Model(Resources<ModelResource>::Get("table")), scene->ecs());
        table.addComponent<RigidBody>(RigidBody(), scene->ecs());
        table.addComponent<Collider>(Collider(ColliderType::AABB, vec3(1.0f, 0.35f, 1.0f), LAB_UP * 0.35f), scene->ecs());
    }

    if (setpiece) {
        auto transform = setpiece.getComponent<Transform>(scene->ecs());
        transform->move(vec3(offset.x, 0.6f, offset.y));
        transform->setParent(table);
    }

    // TODO add table float script

    return room;
}

}  // namespace labeeri
