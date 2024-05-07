#pragma once

#include "Engine/Renderer/Light.h"

namespace labeeri::Engine {

/**
 * @brief The type of a light component.
 */
enum class LightType {
    Directional,
    Point,
    Spot
};

/**
 * @brief Light component.
 */
class Light {
public:
    LightType m_type;
    LightProperties m_properties;
    LightAttenuation m_attenuation;
    f32 m_innerCutoff;
    f32 m_outerCutoff;
    f32 m_intensity = 1.0;

    /**
     * @param type Type of the light.
     * @param properties Properties of the light.
     * @param attenuation Attenuation of the light.
     * @param innerCutoff Inner cutoff of the light.
     * @param outerCutoff Outer cutoff of the light.
     */
    explicit Light(LightType type = LightType::Point, const LightProperties& properties = LightProperties(), const LightAttenuation& attenuation = LightAttenuation(), f32 innerCutoff = 0.82f, f32 outerCutoff = 0.91f)
        : m_type(type), m_properties(properties), m_attenuation(attenuation), m_innerCutoff(innerCutoff), m_outerCutoff(outerCutoff) {
    }

    /**
     * @return The scaled properties of the light by its intensity.
     */
    LightProperties scaledProperties() const {
        return m_properties * m_intensity;
    }

    /**
     * @brief Creates a new directional light component.
     *
     * @param properties Properties of the light.
     * @return The created light component.
     */
    static Light Directional(const LightProperties& properties = DefualtDirectionalLightProperties) {
        return Light(LightType::Directional, properties);
    }

    /**
     * @brief Creates a new point light component.
     *
     * @param properties Properties of the light.
     * @param attenuation Attenuation of the light.
     * @return The created light component.
     */
    static Light Point(const LightProperties& properties = DefualtPointLightProperties, const LightAttenuation& attenuation = LightAttenuation()) {
        return Light(LightType::Point, properties, attenuation);
    }

    /**
     * @brief Creates a new spot light component.
     *
     * @param properties Properties of the light.
     * @param attenuation Attenuation of the light.
     * @param innerCutoff Inner cutoff of the light.
     * @param outerCutoff Outer cutoff of the light.
     * @return The created light component.
     */
    static Light Spot(const LightProperties& properties = DefualtSpotLightProperties, const LightAttenuation& attenuation = LightAttenuation(), f32 innerCutoff = 0.91f, f32 outerCutoff = 0.82f) {
        return Light(LightType::Spot, properties, attenuation, innerCutoff, outerCutoff);
    }
};

}  // namespace labeeri::Engine
