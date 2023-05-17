#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 128) out;

in VData {
    smooth vec3 normal;
    smooth vec2 UV;
} v_data[];

uniform float u_time;
uniform float u_time_multiplier;

uniform mat4 u_PVM_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_model_matrix;
uniform mat4 u_normal_matrix;

uniform sampler2D u_displacement_map;
uniform float u_displacement_strength;

out GData {
    smooth vec3 position_ws;
    smooth vec3 position_es;
    smooth vec3 normal_ws;
    smooth vec3 tangent_ws;
    smooth vec2 UV;
} g_data;


vec2 calculate_UVs(vec2 UV, vec3 position) {
    float time = u_time * u_time_multiplier;
    float scale = 0.0325 + 0.01 * sin(time*2);

    UV =+ position.xz;

    mat3 translate_matrix = transpose(mat3(1.0, 0.0, time,
                                           0.0, 1.0, time * 0.25,
                                           1.0, 0.0, 1.0));

    mat3 scale_matrix = transpose(mat3(scale, 0.0,   0.0,
                                       0.0,   scale, 0.0,
                                       0.0,   0.0,   1.0));

    /*
    mat3 rotate_matrix = transpose(mat3(cos(time), -sin(time), 0.0,
                                        sin(time),  cos(time), 0.0,
                                        0.0,        0.0,       1.0));
    */

    return (translate_matrix * scale_matrix * vec3(UV, 1.0)).xy;
}

vec3 calculate_displacement(vec3 position,vec2 UV, vec3 normal) {
    float displacement = 1.0 - texture(u_displacement_map, UV).r;
    return position + normalize(normal) * displacement * u_displacement_strength;
}

vec3 calculate_normal(vec3 vertA, vec3 vertB, vec3 vertC) {
    vec3 edgeA = vertB - vertA;
    vec3 edgeB = vertC - vertA;
    return normalize(cross(edgeA, edgeB));
}

void instantiate_triangle(vec3 offset) {
    vec4[3] positions;
    vec3[3] positions_ws;
    vec2[3] UVs;

    for (int i = 0; i < 3; i++) {
        vec4 position = gl_in[i].gl_Position + vec4(offset, 0.0);
        UVs[i] = calculate_UVs(v_data[i].UV, position.xyz);
        position.xyz = calculate_displacement(position.xyz, UVs[i], v_data[i].normal);
        positions[i] = position;
        positions_ws[i] = (u_model_matrix * position).xyz;
    }

    vec3 normal_ws = calculate_normal(positions_ws[0], positions_ws[1], positions_ws[2]);

	for (int i = 0; i < 3; i++) {
        vec4 position = positions[i];

        gl_Position = u_PVM_matrix * position;
        g_data.position_ws = positions_ws[i];
        g_data.position_es = (u_view_matrix * u_model_matrix * position).xyz;
        g_data.normal_ws = normal_ws;
        g_data.UV = UVs[i];
        EmitVertex();
    }
    EndPrimitive();
}


void main() {
    for (float x_offset = 0; x_offset <= 6.5; x_offset += 1) {
		for (float z_offset = 0; z_offset <= 6.5; z_offset += 1) {
			instantiate_triangle(vec3(x_offset, 0.0, z_offset));
		}
	}
}
