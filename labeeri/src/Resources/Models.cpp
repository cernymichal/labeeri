#include "Models.h"

#include <glad/glad.h>

#include "Resources/Materials.h"
#include "Resources/plane.h"

namespace labeeri {

static MeshResource createWaterMesh() {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 11 * sizeof(f32) * plane::vertexCount, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(f32) * plane::vertexCount, plane::vertices);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * plane::faceCount * 3, plane::indices, GL_STATIC_DRAW);

    auto& shader = Resources<ShaderResource>::Get("phong");
    if (!shader)
        throw std::runtime_error("No phong shader for default attribute positions");

    GLuint positionLocation = glGetAttribLocation(*shader, "in_position");
    GLuint normalLocation = glGetAttribLocation(*shader, "in_normal");
    GLuint tangentLocation = glGetAttribLocation(*shader, "in_tangent");
    GLuint UVLocation = glGetAttribLocation(*shader, "in_UV");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), nullptr);

    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(3 * sizeof(f32)));

    glEnableVertexAttribArray(tangentLocation);
    glVertexAttribPointer(tangentLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(8 * sizeof(f32) * plane::vertexCount));

    glEnableVertexAttribArray(UVLocation);
    glVertexAttribPointer(UVLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(6 * sizeof(f32)));

    glBindVertexArray(0);
    return MeshResource(VAO, VBO, EBO, plane::faceCount);
}

Ref<ModelResource> waterModel() {
    auto& water = Resources<ModelResource>::Get("water");
    if (water)
        return water;

    return Resources<ModelResource>::Set("water") = makeRef<ModelResource>(makeRef<WaterMaterial>(WaterMaterial()), makeRef<MeshResource>(createWaterMesh()));
}

}  // namespace labeeri
