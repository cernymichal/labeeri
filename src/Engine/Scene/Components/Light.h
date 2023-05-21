#pragma once

#include "Engine/Renderer/Light.h"

namespace labeeri::Engine {

enum class LightType {
    Directional,
    Point,
    Spot
};

/**
 * @brief TODO
 */
class Light {
public:
    LightType m_type;
    LightProperties m_properties;
    LightAttenuation m_attenuation;
    float m_innerCutoff;
    float m_outerCutoff;
    float m_intensity = 1.0;

    explicit Light(LightType type = LightType::Point, const LightProperties& properties = LightProperties(), const LightAttenuation& attenuation = LightAttenuation(), float innerCutoff = 0.91f, float outerCutoff = 0.82f)
        : m_type(type), m_properties(properties), m_attenuation(attenuation), m_innerCutoff(innerCutoff), m_outerCutoff(outerCutoff) {
    }

    LightProperties scaledProperties() const {
        return m_properties * m_intensity;
    }

    /**
     * @brief TODO
     */
    static Light Directional(const LightProperties& properties = DefualtDirectionalLightProperties) {
        return Light(LightType::Directional, properties);
    }

    /**
     * @brief TODO
     */
    static Light Point(const LightProperties& properties = DefualtPointLightProperties, const LightAttenuation& attenuation = LightAttenuation()) {
        return Light(LightType::Point, properties, attenuation);
    }

    /**
     * @brief TODO
     */
    static Light Spot(const LightProperties& properties = DefualtSpotLightProperties, const LightAttenuation& attenuation = LightAttenuation(), float innerCutoff = 0.91f, float outerCutoff = 0.82f) {
        return Light(LightType::Spot, properties, attenuation, innerCutoff, outerCutoff);
    }
};

}  // namespace labeeri::Engine
