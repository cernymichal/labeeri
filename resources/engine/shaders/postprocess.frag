#version 450 core

smooth in vec2 UV;

uniform sampler2D u_color_buffer;
uniform sampler2D u_depth_buffer;
uniform float u_gamma;
uniform float u_exposure;
uniform uvec2 u_screen_size;

out vec4 frag_color;

// https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
vec3 narkowicz_ACES(vec3 color) {
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((color * (a * color + b)) / (color * (c * color + d) + e), 0.0, 1.0);
}

vec4 crosshair() {
	float dist = length((UV  - vec2(0.5)) * u_screen_size);
    float innerMask = 1.0 - step(2.0, dist);
    float outerMask = (1.0 - step(3.0, dist)) * 0.7;
	return vec4(vec3(innerMask), outerMask);
}

void main() {
    vec4 color = texture(u_color_buffer, UV);
    float depth = texture(u_depth_buffer, UV).r;

    vec3 exposed_color = color.rgb * u_exposure;
    vec3 tone_mapped_color = narkowicz_ACES(exposed_color);
    vec3 gamma_corrected_color = pow(tone_mapped_color, vec3(1.0 / u_gamma));

    vec4 crosshair = crosshair();
    gamma_corrected_color.rgb = mix(gamma_corrected_color.rgb, crosshair.rgb, crosshair.a);

    frag_color = vec4(gamma_corrected_color, color.a);
}
