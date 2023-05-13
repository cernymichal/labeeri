#version 450

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VData {
	smooth vec3 position_ws;
	smooth vec3 normal_ws;
	smooth vec3 tangent_ws;
	smooth vec2 UV;
} v_data[];

uniform mat4 u_model_matrix;

out GData {
	smooth vec3 position_ws;
	smooth vec3 normal_ws;
	smooth vec3 tangent_ws;
	smooth vec2 UV;
} g_data;

/*
vec3 calculate_tangent() {
	vec3 edgeA = vs_data[1].position_ws - vs_data[0].position_ws;
	vec3 edgeB = vs_data[2].position_ws - vs_data[0].position_ws;
	vec2 deltaUVA = vs_data[1].UV - vs_data[0].UV;
	vec2 deltaUVB = vs_data[2].UV - vs_data[0].UV;

	float f = 1.0f / (deltaUVA.x * deltaUVB.y - deltaUVA.y * deltaUVB.x);

	vec3 tangent = f * (deltaUVB.y * edgeA - deltaUVA.y * edgeB);

	return normalize(vec3(u_model_matrix * vec4(tangent, 0.0f)));
}
*/

void main() {
	for (int i = 0; i < 3; i++) {
		gl_Position = gl_in[i].gl_Position;
		g_data.position_ws = v_data[i].position_ws;
		g_data.normal_ws = v_data[i].normal_ws;
		g_data.tangent_ws = v_data[i].tangent_ws;
		g_data.UV = v_data[i].UV;
		EmitVertex();
	}

	EndPrimitive();
}
