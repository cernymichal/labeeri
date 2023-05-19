#include "MeshResource.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

MeshResource::~MeshResource() {
    if (m_moved)
        return;

    LAB_RENDERER->deleteMesh(*this);
}

}  // namespace labeeri::Engine
