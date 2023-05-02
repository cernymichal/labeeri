#include "Light.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

void Light::submit(const Transform& transform) const {
    switch (m_type) {
        case LightType::Directional:
            LAB_RENDERER->submitLight(RendererDirectionalLight(transform.forward(), m_properties * m_intensity));
            break;
        case LightType::Point:
            LAB_RENDERER->submitLight(RendererPointLight(transform.position(), m_properties * m_intensity, m_attenuation));
            break;
        case LightType::Spot:
            LAB_RENDERER->submitLight(RendererSpotLight(transform.position(), transform.forward(), m_innerCutOff, m_outerCutOff, m_properties * m_intensity, m_attenuation));
            break;
        default:
            LAB_LOG("Unknown light type");
    }
}

}  // namespace labeeri::Engine
