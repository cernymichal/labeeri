#version 430

smooth in vec3 normal;
smooth in vec2 UV;

uniform float time;

void main() {
    gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);
}
