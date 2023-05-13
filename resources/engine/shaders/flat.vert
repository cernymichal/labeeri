#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_tangent;
layout(location = 3) in vec2 in_UV;

uniform mat4 u_PVM_matrix;

smooth out vec2 UV;

void main() {
    gl_Position = u_PVM_matrix * vec4(in_position, 1);
    UV = in_UV;
}
