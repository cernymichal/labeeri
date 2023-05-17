#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_tangent;
layout(location = 3) in vec2 in_UV;

uniform mat4 u_normal_matrix;

out VData {
    smooth vec3 normal;
    smooth vec2 UV;
} v_data;

void main() {
    gl_Position = vec4(in_position, 1);
    v_data.normal = in_normal;
    v_data.UV = in_UV;
}
