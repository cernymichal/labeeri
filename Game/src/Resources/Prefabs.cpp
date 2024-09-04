#include "Prefabs.h"

Entity roomPrefab(const Ref<Scene>& scene, vec2 offset, Entity setpiece) {
    static bool initialized = false;

    if (!initialized) {
        auto groundMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        groundMaterial->m_diffuseMap = Resources<TextureResource>::Get("textures/concrete_ground/diffuse_lin.png");
        groundMaterial->m_specular = vec3(0.4f);
        groundMaterial->m_normalMap = Resources<TextureResource>::Get("textures/concrete_ground/normal.hdr");
        Resources<MaterialResource>::Set("room_ground") = groundMaterial;
        Resources<ModelResource>::Set("room_ground") = makeRef<ModelResource>(Resources<MaterialResource>::Get("room_ground"), Resources<MeshResource>::Get("models/ground.obj"));

        auto wallMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        wallMaterial->m_diffuseMap = Resources<TextureResource>::Get("textures/concrete_wall/diffuse_lin.png");
        groundMaterial->m_specular = vec3(0.1f);
        wallMaterial->m_normalMap = Resources<TextureResource>::Get("textures/concrete_wall/normal.hdr");
        Resources<MaterialResource>::Set("room_walls") = wallMaterial;
        Resources<ModelResource>::Set("room_walls") = makeRef<ModelResource>(Resources<MaterialResource>::Get("room_walls"), Resources<MeshResource>::Get("models/walls.obj"));

        auto tableMaterial = cloneAs<ShadedMaterialResource>(Resources<MaterialResource>::Get("gray"));
        tableMaterial->m_diffuse = vec3(0.6f);
        tableMaterial->m_specular = vec3(0.7f);
        Resources<MaterialResource>::Set("room_table") = tableMaterial;
        Resources<ModelResource>::Set("room_table") = makeRef<ModelResource>(Resources<MaterialResource>::Get("room_table"), Resources<MeshResource>::Get("models/table.obj"));

        initialized = true;
    }

    auto ground = Entity::Create(scene->ecs());
    auto table = Entity::Create(scene->ecs());

    {  // Ground
        ground.getComponent<Transform>(scene->ecs())->setPosition(vec3(offset.x, 0.0f, offset.y));
        ground.addComponent<Model>(Model(Resources<ModelResource>::Get("room_ground")), scene->ecs());
    }

    {  // Walls
        auto walls = Entity::Create(scene->ecs());
        auto transform = walls.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(offset.x, 0.0f, offset.y));
        transform->setParent(ground);
        walls.addComponent<Model>(Model(Resources<ModelResource>::Get("room_walls")), scene->ecs());
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
            transform->setParent(ground);
        }
    }

    {  // Table
        auto transform = table.getComponent<Transform>(scene->ecs());
        transform->setPosition(vec3(offset.x, 0.0f, offset.y));
        transform->setParent(ground);
        table.addComponent<Model>(Model(Resources<ModelResource>::Get("room_table")), scene->ecs());
        table.addComponent<RigidBody>(RigidBody(), scene->ecs());
        table.addComponent<Collider>(Collider(ColliderType::AABB, vec3(1.0f, 0.35f, 1.0f), VEC_UP * 0.35f), scene->ecs());
    }

    if (setpiece) {
        auto transform = setpiece.getComponent<Transform>(scene->ecs());
        transform->move(vec3(offset.x, 0.6f, offset.y));
        transform->setParent(table);
    }

    // TODO add table f32 script

    return ground;
}
