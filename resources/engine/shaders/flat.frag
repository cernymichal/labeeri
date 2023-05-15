#version 450 core

struct Fog {
	vec3 color;
	float density;
};

smooth in vec2 UV;
smooth in vec3 position_es;

uniform vec3 u_color;
uniform sampler2D u_texture;
uniform bool u_using_texture;

uniform Fog u_fog;

out vec4 fragColor;

vec4 apply_fog(vec4 color) {
	float dist = length(position_es);
	float fog_amount = exp(-pow(u_fog.density * dist, 2.0));
	return vec4(mix(u_fog.color, color.rgb, fog_amount), color.a);
}

void main() {
    vec4 color = u_using_texture ? texture(u_texture, UV) : vec4(u_color, 1.0);
	color = apply_fog(color);
    fragColor = color;
}
