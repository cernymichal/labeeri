#pragma once

#include "Engine/API.h"

namespace labeeri {

/**
 * @brief Entity script that lerps the material to a blood like color áfter click.
 */
class BloodyFaceInteraction : public IScript {
private:
    struct MaterialSample {
        vec3 diffuse;
        vec3 specular;
        f32 shininess;
        f32 metallic;
    };

public:
    explicit BloodyFaceInteraction(Entity entity)
        : IScript(entity) {
    }

protected:
    virtual void onEntityClick(const EntityClickEvent& e) override {
        if (m_started)
            return;

        auto material = castRef<ShadedMaterialResource>(m_entity.getComponent<Model>()->m_ref->m_material);
        m_originalMaterial.diffuse = material->m_diffuse;
        m_originalMaterial.specular = material->m_specular;
        m_originalMaterial.shininess = material->m_shininess;
        m_originalMaterial.metallic = material->m_metallic;

        m_started = true;
        m_startTime = LAB_CURRENT_SCENE->time();
    }

    virtual void onFixedUpdate(const FixedUpdateEvent& e) override {
        auto currentTime = LAB_CURRENT_SCENE->time();
        if (!m_started || (m_started && currentTime > m_startTime + m_duration))
            return;

        auto factor = glm::smoothstep(0.0, 1.0, (currentTime - m_startTime) / m_duration);
        auto material = castRef<ShadedMaterialResource>(m_entity.getComponent<Model>()->m_ref->m_material);
        material->m_diffuse = glm::mix(m_originalMaterial.diffuse, m_targetMaterial.diffuse, factor);
        material->m_specular = glm::mix(m_originalMaterial.specular, m_targetMaterial.specular, factor);
        material->m_shininess = glm::mix(m_originalMaterial.shininess, m_targetMaterial.shininess, factor);
        material->m_metallic = glm::mix(m_originalMaterial.metallic, m_targetMaterial.metallic, factor);
    }

private:
    bool m_started = false;
    f64 m_startTime = 0.0;
    f64 m_duration = 3.0;

    MaterialSample m_originalMaterial = {
        vec3(0.0f),
        vec3(0.0f),
        0.0f,
        0.0f};
    MaterialSample m_targetMaterial = {
        vec3(0.39f, 0.05f, 0.09f),
        vec3(0.5f, 0.49f, 0.94f),
        128.0f,
        0.4f};
};

}  // namespace labeeri
