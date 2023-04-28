#version 430

smooth in vec3 normal;
smooth in vec2 UV;

uniform float time;

out vec4 fragColor;

void main() {
    fragColor = vec4(0.9, 0.0, 0.9, 1.0);
}
