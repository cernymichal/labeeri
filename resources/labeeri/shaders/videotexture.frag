#version 450 core

struct Fog {
	vec3 color;
	float density;
};

smooth in vec2 UV;
smooth in vec3 position_es;

uniform sampler2DRect u_texture;
uniform uvec2 u_frame_size;
uniform uvec2 u_frame_count;
uniform float u_fps;

uniform float u_time;

uniform Fog u_fog;

out vec4 frag_color;

vec3 apply_fog(vec3 color) {
	float dist = length(position_es);
	float fog_amount = exp(-pow(u_fog.density * dist, 2.0));
	return mix(u_fog.color, color, fog_amount);
}

void main() {
	uint frame = uint(u_time * u_fps) % (u_frame_count.x * u_frame_count.y);
	uint x = frame % u_frame_count.x;
	uint y = frame / u_frame_count.x;
	vec2 uv = vec2(x, y) * u_frame_size + UV * u_frame_size;

    vec4 color = texture(u_texture, uv);

	color.rgb = apply_fog(color.rgb);
    frag_color = color;
}
