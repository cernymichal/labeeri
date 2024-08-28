#pragma once

#include "Renderer/RendererParameters.h"

namespace labeeri {

struct ImageResource {
    uvec2 size = uvec2(0);
    void* data = nullptr;
    TextureDataType dataType = TextureDataType::UByte;
    TextureFormat format = TextureFormat::RGB;
    TextureInternalFormat internalFormat = TextureInternalFormat::RGB;

    ImageResource() = default;

    ImageResource(uvec2 size, void* data, TextureDataType dataType, TextureFormat format, TextureInternalFormat internalFormat)
        : size(size), data(data), dataType(dataType), format(format), internalFormat(internalFormat) {
    }

    ImageResource(const ImageResource& other) = delete;

    ImageResource(ImageResource&& other) noexcept
        : size(other.size), data(other.data), dataType(other.dataType), format(other.format), internalFormat(other.internalFormat) {
        other.data = nullptr;
    }

    virtual ~ImageResource() = default;
};

}  // namespace labeeri
