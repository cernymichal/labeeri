#version 450 core

in vec3 view_direction;

uniform samplerCube u_skybox;

out vec4 frag_color;

void main() {
    frag_color = texture(u_skybox, view_direction);
}
