#include "log.h"

#include "GL/glew.h"

namespace labeeri::engine {

void logOGLError(const char* file, int line) {
    for (GLenum error = glGetError(); error != GL_NO_ERROR; error = glGetError()) {
        std::string errorStr = "UNKNOWN";
        switch (error) {
            case GL_INVALID_ENUM:
                errorStr = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                errorStr = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                errorStr = "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                errorStr = "GL_OUT_OF_MEMORY";
                break;
            default:;
        }

        LAB_LOG("OpenGL error: " << errorStr << " in " << file << " at line " << line);
    }
}

}  // namespace labeeri::engine