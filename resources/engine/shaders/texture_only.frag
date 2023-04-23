#version 430

smooth in vec2 UV;

void main() {
    gl_FragColor = vec4(UV.x, UV.y, 0.0, 1.0);
}
