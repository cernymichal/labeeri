#version 430

layout(location = 0) in vec3 position_in;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 UV_in;

uniform float time;

uniform mat4 PVM_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

smooth out vec2 UV;

void main() {
    gl_Position = PVM_matrix * vec4(position_in, 1);
    UV = UV_in;
}
