#include "MeshResource.h"

#include "Renderer/IRenderer.h"

namespace labeeri {

MeshResource::~MeshResource() {
    if (m_moved)
        return;

    if (LAB_RENDERER)
        LAB_RENDERER->deleteMesh(*this);
}

}  // namespace labeeri
