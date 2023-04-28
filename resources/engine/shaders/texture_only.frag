#version 430

smooth in vec2 UV;

out vec4 fragColor;

void main() {
    fragColor = vec4(UV.x, UV.y, 0.0, 1.0);
}
