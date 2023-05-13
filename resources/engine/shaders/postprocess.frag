#version 450

smooth in vec2 UV;

uniform sampler2D u_color_buffer;
uniform sampler2D u_depth_buffer;
uniform float u_gamma;

out vec4 fragColor;

void main() {
    vec4 color = vec4(texture(u_color_buffer, UV).rgb, 1.0f);
	float depth = texture(u_depth_buffer, UV).r;

	fragColor = vec4(pow(color.rgb, vec3(1.0 / u_gamma)), color.a);
}
