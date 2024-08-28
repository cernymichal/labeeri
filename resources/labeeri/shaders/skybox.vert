#version 460 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_tangent;
layout(location = 3) in vec2 in_UV;

uniform mat4 u_view_matrix_inverse;
uniform mat4 u_projection_matrix_inverse;

out vec3 view_direction;

void main() {
    gl_Position = vec4(in_position.xy, 0.0, 1.0);
    view_direction = mat3(u_view_matrix_inverse) * (u_projection_matrix_inverse * vec4(in_position.xy, 0.0, 1.0)).xyz;
}
