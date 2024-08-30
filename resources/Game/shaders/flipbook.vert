#version 460 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_tangent;
layout(location = 3) in vec2 in_UV;

uniform mat4 u_PVM_matrix;
uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;

smooth out vec2 UV;
smooth out vec3 position_es;

void main() {
    gl_Position = u_PVM_matrix * vec4(in_position, 1);
    UV = in_UV;
    position_es = (u_view_matrix * u_model_matrix * vec4(in_position, 1)).xyz;
}
