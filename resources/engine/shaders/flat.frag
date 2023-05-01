#version 430

smooth in vec2 UV;

uniform vec3 u_color;
uniform sampler2D u_texture;
uniform bool u_using_texture;

out vec4 fragColor;

void main() {
    fragColor = u_using_texture ? texture(u_texture, UV) : vec4(u_color, 1.0);
}