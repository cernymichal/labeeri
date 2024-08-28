#version 460 core

uniform float u_time;
uniform vec3 u_camera_position;

out vec4 frag_color;

void main() {
    frag_color = vec4(0.9, 0.0, 0.9, 1.0);
}
