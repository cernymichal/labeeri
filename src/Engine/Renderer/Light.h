#pragma once

namespace labeeri::Engine {

struct RendererLightAttenutaion {
    float constant;
    float linear;
    float quadratic;

    RendererLightAttenutaion(float constant, float linear, float quadratic)
        : constant(constant), linear(linear), quadratic(quadratic) {
    }
};

struct RendererLightProperties {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    RendererLightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {
    }
};

struct RendererDirectionalLight {
    glm::vec3 direction;

    RendererLightProperties properties;

    RendererDirectionalLight(const glm::vec3& direction, const RendererLightProperties& properties)
        : direction(direction), properties(properties) {
    }
};

struct RendererPointLight {
    glm::vec3 position;

    RendererLightProperties properties;
    RendererLightAttenutaion attenutaion;

    RendererPointLight(const glm::vec3& position, const RendererLightProperties& properties, const RendererLightAttenutaion& attenutaion)
        : position(position), properties(properties), attenutaion(attenutaion) {
    }
};

struct RendererSpotLight {
    glm::vec3 position;
    glm::vec3 direction;

    float cutOff;
    float outerCutOff;

    RendererLightProperties properties;
    RendererLightAttenutaion attenutaion;

    RendererSpotLight(const glm::vec3& position, const glm::vec3& direction, float cutOff, float outerCutOff, const RendererLightProperties& properties, const RendererLightAttenutaion& attenutaion)
        : position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff), properties(properties), attenutaion(attenutaion) {
    }
};

}  // namespace labeeri::Engine