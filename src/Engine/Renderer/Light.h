#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
struct LightAttenuation {
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    LightAttenuation() {
    }

    LightAttenuation(float constant, float linear, float quadratic)
        : constant(constant), linear(linear), quadratic(quadratic) {
    }
};

/**
 * @brief TODO
 */
struct LightProperties {
    glm::vec3 ambient = glm::vec3(1.0, 0.97, 0.98) * 0.05f;
    glm::vec3 diffuse = glm::vec3(1.0, 0.97, 0.98);  // 6400K
    glm::vec3 specular = glm::vec3(1.0);

    LightProperties() {
    }

    LightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {
    }

    inline LightProperties operator*(float factor) const {
        LightProperties result(*this);
        result.ambient *= factor;
        result.diffuse *= factor;
        result.specular *= factor;
        return result;
    }
};

/**
 * @brief TODO
 */
struct RendererDirectionalLight {
    glm::vec3 direction;

    LightProperties properties;

    RendererDirectionalLight(const glm::vec3& direction, const LightProperties& properties)
        : direction(direction), properties(properties) {
    }
};

/**
 * @brief TODO
 */
struct RendererPointLight {
    glm::vec3 position;

    LightProperties properties;
    LightAttenuation attenuation;

    RendererPointLight(const glm::vec3& position, const LightProperties& properties, const LightAttenuation& attenuation)
        : position(position), properties(properties), attenuation(attenuation) {
    }
};

/**
 * @brief TODO
 */
struct RendererSpotLight {
    glm::vec3 position;
    glm::vec3 direction;

    float innerCutOff;
    float outerCutOff;

    LightProperties properties;
    LightAttenuation attenuation;

    RendererSpotLight(const glm::vec3& position, const glm::vec3& direction, float innerCutOff, float outerCutOff, const LightProperties& properties, const LightAttenuation& attenuation)
        : position(position), direction(direction), innerCutOff(innerCutOff), outerCutOff(outerCutOff), properties(properties), attenuation(attenuation) {
    }
};

}  // namespace labeeri::Engine