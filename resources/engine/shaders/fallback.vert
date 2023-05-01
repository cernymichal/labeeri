#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_UV;

uniform float u_time;
uniform vec3 u_camera_position;

uniform mat4 u_PVM_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_model_matrix;
uniform mat4 u_normal_matrix;

smooth out vec3 normal;
smooth out vec2 UV;

void main() {
    gl_Position = u_PVM_matrix * vec4(in_position, 1);
    normal = normalize((u_view_matrix * u_normal_matrix * vec4(in_normal, 0.0)).xyz);
    UV = in_UV;
}
