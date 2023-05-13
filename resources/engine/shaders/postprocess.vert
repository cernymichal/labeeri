#version 450

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_tangent;
layout(location = 3) in vec2 in_UV;

smooth out vec2 UV;

void main() {
    gl_Position = vec4(in_position, 1.0f);
    UV = in_UV;
}
