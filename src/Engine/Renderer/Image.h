#pragma once

#include "Engine/Renderer/RendererParameters.h"

namespace labeeri::Engine {

struct Image {
    glm::uvec2 size = glm::uvec2(0);
    void* data = nullptr;
    TextureDataType dataType = TextureDataType::UByte;
    TextureFormat format = TextureFormat::RGB;
    TextureInternalFormat internalFormat = TextureInternalFormat::RGB;

    Image() = default;

    Image(glm::uvec2 size, void* data, TextureDataType dataType, TextureFormat format, TextureInternalFormat internalFormat)
        : size(size), data(data), dataType(dataType), format(format), internalFormat(internalFormat) {
    }

    Image(const Image& other) = delete;

    Image(Image&& other) noexcept
        : size(other.size), data(other.data), dataType(other.dataType), format(other.format), internalFormat(other.internalFormat) {
        other.data = nullptr;
    }

    virtual ~Image() = default;
};

}  // namespace labeeri::Engine
