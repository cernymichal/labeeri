#version 460 core

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

uniform float u_alpha;

out vec4 frag_color;

vec3 apply_fog(vec3 color) {
	float dist = length(position_es);
	float fog_amount = exp(-pow(u_fog.density * dist, 2.0));
	return mix(u_fog.color, color, fog_amount);
}

void main() {
    vec3 color = u_using_texture ? texture(u_texture, UV).rgb : u_color;
	color = apply_fog(color);
    frag_color = vec4(color, u_alpha);
}
