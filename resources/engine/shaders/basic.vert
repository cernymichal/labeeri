#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 UV;

uniform float time;

uniform mat4 PVM_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

smooth out vec3 normal_out;
smooth out vec2 UV_out;

void main() {
    gl_Position = PVM_matrix * vec4(position, 1);
    normal_out = normalize((view_matrix * normal_matrix * vec4(normal, 0.0)).xyz);
    UV_out = UV;
}
