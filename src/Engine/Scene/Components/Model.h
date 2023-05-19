#pragma once

#include "Engine/Resources/ModelResource.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Model {
public:
    Ref<ModelResource> m_ref;

    /**
     * @brief TODO
     */
    Ref<ModelResource>& operator*() {
        return m_ref;
    }
};

}  // namespace labeeri::Engine
