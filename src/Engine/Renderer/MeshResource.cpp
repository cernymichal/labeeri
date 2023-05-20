#include "MeshResource.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

MeshResource::~MeshResource() {
    if (m_moved)
        return;

    if (LAB_RENDERER)
        LAB_RENDERER->deleteMesh(*this);
}

}  // namespace labeeri::Engine
