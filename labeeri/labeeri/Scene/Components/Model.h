#pragma once

#include "Resources/ModelResource.h"

namespace labeeri {

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

}  // namespace labeeri
