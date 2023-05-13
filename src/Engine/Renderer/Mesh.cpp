#include "Mesh.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

Mesh::~Mesh() {
    if (m_moved)
        return;

    LAB_RENDERER->deleteMesh(*this);
}

}  // namespace labeeri::Engine
