#include "EntityWindow.h"

#include <imgui.h>

#include "Engine/Resources/Resources.h"
#include "Engine/Scene/Components/Light.h"
#include "Engine/Scene/Components/Model.h"
#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

static void materialSectionDefault(const Ref<MaterialResource>& material) {
    ImGui::SeparatorText("Unknown Material");
}

static void materialSectionFlat(const Ref<FlatMaterialResource>& material) {
    ImGui::SeparatorText("Flat Material");

    ImGui::ColorEdit3("Color", glm::value_ptr(material->m_color));
    ImGui::SliderFloat("Alpha", &material->m_alpha, 0.0f, 1.0f);

    bool usingTexture = material->m_texture != nullptr;

    ImGui::BeginDisabled();
    ImGui::Checkbox("Texture", &usingTexture);
    ImGui::EndDisabled();
}

static void materialSectionShaded(const Ref<ShadedMaterialResource>& material) {
    ImGui::SeparatorText("Shaded Material");

    ImGui::ColorEdit3("Diffuse", glm::value_ptr(material->m_diffuse));
    ImGui::ColorEdit3("Specular", glm::value_ptr(material->m_specular));
    ImGui::InputFloat("Shininess", &material->m_shininess);
    ImGui::SliderFloat("Metallic", &material->m_metallic, 0.0f, 1.0f);
    ImGui::SliderFloat("Alpha", &material->m_alpha, 0.0f, 1.0f);

    bool usingDiffuseMap = material->m_diffuseMap != nullptr;
    bool usingSpecularMap = material->m_specularMap != nullptr;
    bool usingMetallicMap = material->m_metallicMap != nullptr;
    bool usingNormalMap = material->m_normalMap != nullptr;

    ImGui::BeginDisabled();
    ImGui::Checkbox("Diffuse Map", &usingDiffuseMap);
    ImGui::Checkbox("Specular Map", &usingSpecularMap);
    ImGui::Checkbox("Metallic Map", &usingMetallicMap);
    ImGui::Checkbox("Normal Map", &usingNormalMap);
    ImGui::EndDisabled();
}

static void meshSection(const Ref<MeshResource>& mesh) {
    ImGui::SeparatorText("Mesh");

    ImGui::Text("Vertex Array Object: %d", mesh->m_vertexArrayObject);
    ImGui::Text("Triangle Count : %d", mesh->m_triangleCount);
}

static void modelSection(Model* model) {
    if (!model)
        return;

    auto& resource = model->m_ref;

    if (!ImGui::CollapsingHeader("Model"))
        return;

    if (!resource)
        return;

    if (resource->m_material) {
        if (castRef<ShadedMaterialResource>(resource->m_material))
            materialSectionShaded(castRef<ShadedMaterialResource>(resource->m_material));
        else if (castRef<FlatMaterialResource>(resource->m_material))
            materialSectionFlat(castRef<FlatMaterialResource>(resource->m_material));
        else
            materialSectionDefault(resource->m_material);
    }

    if (resource->m_mesh)
        meshSection(resource->m_mesh);

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
}

static const char* lightTypeToString(LightType type) {
    switch (type) {
        case LightType::Directional:
            return "Directional";
        case LightType::Point:
            return "Point";
        case LightType::Spot:
            return "Spot";
        default:
            return "Unknown";
    }
}

static void lightSection(Light* light) {
    if (!light)
        return;

    if (!ImGui::CollapsingHeader("Light"))
        return;

    if (ImGui::BeginCombo("Light Type", lightTypeToString(light->m_type))) {
        for (LightType type : {LightType::Directional, LightType::Point, LightType::Spot}) {
            if (ImGui::Selectable(lightTypeToString(type), light->m_type == type))
                light->m_type = type;
            if (light->m_type == type)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::SeparatorText("Properties");
    ImGui::ColorEdit3("Ambient", glm::value_ptr(light->m_properties.ambient));
    ImGui::ColorEdit3("Diffuse", glm::value_ptr(light->m_properties.diffuse));
    ImGui::ColorEdit3("Specular", glm::value_ptr(light->m_properties.specular));
    ImGui::InputFloat("Intensity", &light->m_intensity);

    ImGui::SeparatorText("Attenuation");
    ImGui::InputFloat("Constant", &light->m_attenuation.constant);
    ImGui::InputFloat("Linear", &light->m_attenuation.linear);
    ImGui::InputFloat("Quadratic", &light->m_attenuation.quadratic);

    ImGui::SeparatorText("Cutoff");
    ImGui::InputFloat("Inner", &light->m_innerCutoff);
    ImGui::InputFloat("Outer", &light->m_outerCutoff);

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
}

bool EntityWindow::draw() {
    auto transform = m_entity.getComponent<Transform>();
    m_position = transform->position();
    m_rotationEuler = glm::degrees(glm::eulerAngles(transform->rotation()));
    m_scale = transform->scale();

    ImGui::SetNextWindowSize(ImVec2(300, 800), ImGuiCond_Once);

    bool shouldContinue = true;
    ImGui::Begin(m_name.c_str(), &shouldContinue);

    if (ImGui::CollapsingHeader("Transform")) {
        if (ImGui::InputFloat3("Location", glm::value_ptr(m_position)))
            transform->setPosition(m_position);

        if (ImGui::InputFloat3("Rotation", glm::value_ptr(m_rotationEuler)))
            transform->setRotation(glm::radians(m_rotationEuler));

        if (ImGui::InputFloat3("Scale", glm::value_ptr(m_scale)))
            transform->setScale(m_scale);

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
    }

    modelSection(m_entity.getComponent<Model>());
    lightSection(m_entity.getComponent<Light>());

    ImGui::End();

    return shouldContinue;
}

}  // namespace labeeri::Engine
