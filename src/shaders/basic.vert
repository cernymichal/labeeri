#version 430

in vec3 position;
in vec3 normal;
in vec2 UV;

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
