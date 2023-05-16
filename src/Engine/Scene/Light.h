#pragma once

#include "Engine/Renderer/Light.h"
#include "Engine/Scene/Transform.h"

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

    Light(LightType type, const LightProperties& properties, const LightAttenuation& attenuation = LightAttenuation(), float innerCutoff = 0.91, float outerCutoff = 0.82)
        : m_type(type), m_properties(properties), m_attenuation(attenuation), m_innerCutoff(innerCutoff), m_outerCutoff(outerCutoff) {
    }

    /**
     * @brief TODO
     */
    void submit(const Transform& transform) const;

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
    static Light Spot(const LightProperties& properties = DefualtSpotLightProperties, const LightAttenuation& attenuation = LightAttenuation(), float innerCutoff = 0.91, float outerCutoff = 0.82) {
        return Light(LightType::Spot, properties, attenuation, innerCutoff, outerCutoff);
    }
};

}  // namespace labeeri::Engine
