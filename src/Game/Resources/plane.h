#pragma once

namespace labeeri::plane {

constexpr int attribsPerVertex = 8;
constexpr int vertexCount = 25;
constexpr int faceCount = 32;
constexpr float vertices[] = {
    0.25f,0.0f,-0.25f,0.0f,1.0f,0.0f,0.75f,0.75f,
    0.5f,0.0f,-0.25f,0.0f,1.0f,0.0f,1.0f,0.75f,
    0.5f,0.0f,-0.5f,0.0f,1.0f,0.0f,1.0f,1.0f,
    0.25f,0.0f,-0.5f,0.0f,1.0f,0.0f,0.75f,1.0f,
    -0.5f,0.0f,-0.25f,0.0f,1.0f,0.0f,0.0f,0.75f,
    -0.25f,0.0f,-0.25f,0.0f,1.0f,0.0f,0.25f,0.75f,
    -0.25f,0.0f,-0.5f,0.0f,1.0f,0.0f,0.25f,1.0f,
    -0.5f,0.0f,-0.5f,0.0f,1.0f,0.0f,0.0f,1.0f,
    0.0f,0.0f,-0.25f,0.0f,1.0f,0.0f,0.5f,0.75f,
    0.0f,0.0f,-0.5f,0.0f,1.0f,0.0f,0.5f,1.0f,
    -0.5f,0.0f,0.5f,0.0f,1.0f,0.0f,0.0f,0.0f,
    -0.25f,0.0f,0.5f,0.0f,1.0f,0.0f,0.25f,0.0f,
    -0.25f,0.0f,0.25f,0.0f,1.0f,0.0f,0.25f,0.25f,
    -0.5f,0.0f,0.25f,0.0f,1.0f,0.0f,0.0f,0.25f,
    -0.25f,0.0f,0.0f,0.0f,1.0f,0.0f,0.25f,0.5f,
    -0.5f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.5f,
    0.0f,0.0f,0.5f,0.0f,1.0f,0.0f,0.5f,0.0f,
    0.0f,0.0f,0.25f,0.0f,1.0f,0.0f,0.5f,0.25f,
    0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.5f,0.5f,
    0.25f,0.0f,0.5f,0.0f,1.0f,0.0f,0.75f,0.0f,
    0.25f,0.0f,0.25f,0.0f,1.0f,0.0f,0.75f,0.25f,
    0.25f,0.0f,0.0f,0.0f,1.0f,0.0f,0.75f,0.5f,
    0.5f,0.0f,0.5f,0.0f,1.0f,0.0f,1.0f,0.0f,
    0.5f,0.0f,0.25f,0.0f,1.0f,0.0f,1.0f,0.25f,
    0.5f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,0.5f,
};
constexpr unsigned indices[] = {
    0, 1, 2,
    0, 2, 3,
    4, 5, 6,
    4, 6, 7,
    5, 8, 9,
    5, 9, 6,
    8, 0, 3,
    8, 3, 9,
    10, 11, 12,
    10, 12, 13,
    13, 12, 14,
    13, 14, 15,
    15, 14, 5,
    15, 5, 4,
    11, 16, 17,
    11, 17, 12,
    12, 17, 18,
    12, 18, 14,
    14, 18, 8,
    14, 8, 5,
    16, 19, 20,
    16, 20, 17,
    17, 20, 21,
    17, 21, 18,
    18, 21, 0,
    18, 0, 8,
    19, 22, 23,
    19, 23, 20,
    20, 23, 24,
    20, 24, 21,
    21, 24, 1,
    21, 1, 0,
};

} // namespace labeeri