#pragma once

namespace labeeri::Engine {

/**
 * @brief Describes the attenuation of a light.
 */
struct LightAttenuation {
    f32 constant = 1.0f;
    f32 linear = 0.0f;
    f32 quadratic = 0.1f;

    LightAttenuation() = default;

    LightAttenuation(f32 constant, f32 linear, f32 quadratic)
        : constant(constant), linear(linear), quadratic(quadratic) {
    }
};

/**
 * @brief Lights color and other properties.
 */
struct LightProperties {
    vec3 ambient = vec3(1.0, 0.97, 0.98) * 0.05f;
    vec3 diffuse = vec3(1.0, 0.97, 0.98);  // 6400K
    vec3 specular = vec3(1.0);

    LightProperties() = default;

    /**
     * @param ambient The ambient color of the light.
     * @param diffuse The diffuse color of the light.
     * @param specular The specular color of the light.
     */
    LightProperties(const vec3& ambient, const vec3& diffuse, const vec3& specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {
    }

    /**
     * @brief Multiplies all properties with the given factor.
     *
     * @param factor The factor to multiply with.
     * @return The multiplied properties.
     */
    LightProperties operator*(f32 factor) const {
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
 * @brief Directional light for the renderer.
 */
struct RendererDirectionalLight {
    vec3 direction;

    LightProperties properties;

    /*
     * @param direction The direction of the light.
     * @param properties The properties of the light.
     */
    RendererDirectionalLight(const vec3& direction, const LightProperties& properties)
        : direction(direction), properties(properties) {
    }
};

/**
 * @brief Point light for the renderer.
 */
struct RendererPointLight {
    vec3 position;

    LightProperties properties;
    LightAttenuation attenuation;

    /*
     * @param position The position of the light.
     * @param properties The properties of the light.
     * @param attenuation The attenuation of the light.
     */
    RendererPointLight(const vec3& position, const LightProperties& properties, const LightAttenuation& attenuation)
        : position(position), properties(properties), attenuation(attenuation) {
    }
};

/**
 * @brief Spot light for the renderer.
 */
struct RendererSpotLight {
    vec3 position;
    vec3 direction;

    f32 innerCutoff;
    f32 outerCutoff;

    LightProperties properties;
    LightAttenuation attenuation;

    /*
     * @param position The position of the light.
     * @param direction The direction of the light.
     * @param innerCutoff The inner cutoff of the light.
     * @param outerCutoff The outer cutoff of the light.
     * @param properties The properties of the light.
     * @param attenuation The attenuation of the light.
     */
    RendererSpotLight(const vec3& position, const vec3& direction, f32 innerCutoff, f32 outerCutoff, const LightProperties& properties, const LightAttenuation& attenuation)
        : position(position), direction(direction), innerCutoff(innerCutoff), outerCutoff(outerCutoff), properties(properties), attenuation(attenuation) {
    }
};

}  // namespace labeeri::Engine