#pragma once

#include "Engine/Resources/ModelResource.h"

namespace labeeri::Engine {

/**
 * @brief Model component. Only holds a reference to a model resource.
 */
class Model {
public:
    Ref<ModelResource> m_ref;    

    /**
     * @return The model resource.
     */
    Ref<ModelResource>& operator*() {
        return m_ref;
    }
};

}  // namespace labeeri::Engine
