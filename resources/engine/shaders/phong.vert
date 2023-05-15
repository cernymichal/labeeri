#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_tangent;
layout(location = 3) in vec2 in_UV;

uniform mat4 u_PVM_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_model_matrix;
uniform mat4 u_normal_matrix;

out VData {
    smooth vec3 position_ws;
    smooth vec3 position_es;
    smooth vec3 normal_ws;
    smooth vec3 tangent_ws;
    smooth vec2 UV;
} vs_data;

void main() {
    gl_Position = u_PVM_matrix * vec4(in_position, 1);
    vs_data.position_ws = (u_model_matrix * vec4(in_position, 1)).xyz;
    vs_data.position_es = (u_view_matrix * u_model_matrix * vec4(in_position, 1)).xyz;
    vs_data.normal_ws = normalize((u_normal_matrix * vec4(in_normal, 0.0)).xyz);
    vs_data.tangent_ws = normalize((u_normal_matrix * vec4(in_tangent, 0.0)).xyz);
    vs_data.UV = in_UV;
}
