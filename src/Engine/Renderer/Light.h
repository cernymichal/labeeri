#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
struct LightAttenuation {
    float constant = 1.0f;
    float linear = 0.0f;
    float quadratic = 0.1f;

    LightAttenuation() = default;

    LightAttenuation(float constant, float linear, float quadratic)
        : constant(constant), linear(linear), quadratic(quadratic) {
    }
};

/**
 * @brief TODO
 */
struct LightProperties {
    vec3 ambient = vec3(1.0, 0.97, 0.98) * 0.05f;
    vec3 diffuse = vec3(1.0, 0.97, 0.98);  // 6400K
    vec3 specular = vec3(1.0);

    LightProperties() = default;

    LightProperties(const vec3& ambient, const vec3& diffuse, const vec3& specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {
    }

    LightProperties operator*(float factor) const {
        LightProperties result(*this);
        result.ambient *= factor;
        result.diffuse *= factor;
        result.specular *= factor;
        return result;
    }
};

const auto DefualtDirectionalLightProperties = LightProperties();
const auto DefualtPointLightProperties = LightProperties(vec3(0.1f), vec3(1.0f), vec3(1.0f));
const auto DefualtSpotLightProperties = LightProperties(vec3(0.0f), vec3(1.0f), vec3(1.0f));

/**
 * @brief TODO
 */
struct RendererDirectionalLight {
    vec3 direction;

    LightProperties properties;

    RendererDirectionalLight(const vec3& direction, const LightProperties& properties)
        : direction(direction), properties(properties) {
    }
};

/**
 * @brief TODO
 */
struct RendererPointLight {
    vec3 position;

    LightProperties properties;
    LightAttenuation attenuation;

    RendererPointLight(const vec3& position, const LightProperties& properties, const LightAttenuation& attenuation)
        : position(position), properties(properties), attenuation(attenuation) {
    }
};

/**
 * @brief TODO
 */
struct RendererSpotLight {
    vec3 position;
    vec3 direction;

    float innerCutoff;
    float outerCutoff;

    LightProperties properties;
    LightAttenuation attenuation;

    RendererSpotLight(const vec3& position, const vec3& direction, float innerCutoff, float outerCutoff, const LightProperties& properties, const LightAttenuation& attenuation)
        : position(position), direction(direction), innerCutoff(innerCutoff), outerCutoff(outerCutoff), properties(properties), attenuation(attenuation) {
    }
};

}  // namespace labeeri::Engine