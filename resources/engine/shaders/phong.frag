#version 430

#define MAX_DIRECTIONAL_LIGHTS 1
#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS 4

#define BLINN

struct Material {
	vec3 diffuse;
	sampler2D diffuse_map;
	bool using_diffuse_map;

	vec3 specular;
	sampler2D specular_map;
	bool using_specular_map;

	float shininess;

	sampler2D normal_map;
	bool using_normal_map;
};

struct MaterialSample {
	vec3 diffuse;
	vec3 specular;
	float shininess;
	vec3 normal;
};

struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

struct LightProperties {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirectionalLight {
    vec3 direction;

    LightProperties properties;
};

struct PointLight {    
    vec3 position;

    LightProperties properties;
	Attenuation attenuation;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	float innerCutOff;
	float outerCutOff;

    LightProperties properties;
	Attenuation attenuation;
};

in GData {
	smooth vec3 position_ws;
	smooth vec3 normal_ws;
	smooth vec3 tangent_ws;
	smooth vec2 UV;
} g_data;

uniform vec3 u_camera_position;

uniform DirectionalLight u_directional_lights[MAX_DIRECTIONAL_LIGHTS];
uniform int u_directional_light_count;
uniform PointLight u_point_lights[MAX_POINT_LIGHTS];
uniform int u_point_light_count;
uniform SpotLight u_spot_lights[MAX_SPOT_LIGHTS];
uniform int u_spot_light_count;

uniform Material u_material;

out vec4 fragColor;

mat3 calculate_TBN_matrix() {
	vec3 T = normalize(g_data.tangent_ws);
	vec3 N = normalize(g_data.normal_ws);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);
	
	return mat3(T, B, N);
}

MaterialSample sample_material() {
	MaterialSample result;
	result.diffuse = u_material.using_diffuse_map ? texture(u_material.diffuse_map, g_data.UV).rgb : u_material.diffuse;
	result.specular = u_material.using_specular_map ? texture(u_material.specular_map, g_data.UV).rgb : u_material.specular;
	result.shininess = u_material.shininess;

	if (u_material.using_normal_map) {
		mat3 TBN_matrix = calculate_TBN_matrix();
		result.normal = normalize(TBN_matrix * (texture(u_material.normal_map, g_data.UV).xyz * 2.0f - 1.0f));
	}
	else
		result.normal = normalize(g_data.normal_ws);

	return result;
}

vec3 phong(LightProperties light, MaterialSample material, vec3 view_direction, vec3 light_direction) {
	vec3 ambient = light.ambient * material.diffuse;

	vec3 diffuse = light.diffuse * material.diffuse * max(dot(material.normal, light_direction), 0.0);

	float specular_visibility = step(0.0, dot(material.normal, light_direction));
	#ifdef BLINN
	vec3 half_direction = normalize(view_direction + light_direction);
	vec3 specular = light.specular * material.specular * pow(max(dot(material.normal, half_direction), 0.0), material.shininess) * specular_visibility;
	#else
	vec3 reflect_direction = reflect(-light_direction, material.normal);
	vec3 specular = light.specular * material.specular * pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess) * specular_visibility;
	#endif

	return ambient + diffuse + specular;
}

vec3 calculate_directional_light(DirectionalLight light, MaterialSample material, vec3 view_direction) {
	return phong(light.properties, material, view_direction, normalize(-light.direction));
}

vec3 calculate_point_light(PointLight light, MaterialSample material, vec3 view_direction) {
	vec3 light_direction = normalize(light.position - g_data.position_ws);

	float distance = length(light.position - g_data.position_ws);
	float attenuation = 1.0 / (light.attenuation.constant + light.attenuation.linear * distance + light.attenuation.quadratic * (distance * distance));

	return phong(light.properties, material, view_direction, light_direction) * attenuation;
}

vec3 calculate_spot_light(SpotLight light, MaterialSample material, vec3 view_direction) {
	vec3 light_direction = normalize(light.position - g_data.position_ws);

	float distance = length(light.position - g_data.position_ws);
	float attenuation = 1.0 / (light.attenuation.constant + light.attenuation.linear * distance + light.attenuation.quadratic * (distance * distance));

	float theta = dot(light_direction, normalize(-light.direction));
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	return phong(light.properties, material, view_direction, light_direction) * attenuation * intensity;
}

void main() {
	vec3 view_direction = normalize(u_camera_position - g_data.position_ws);
	MaterialSample material_sample = sample_material();

	vec3 result = vec3(0.0);

	for (int i = 0; i < u_directional_light_count; i++) 
		result += calculate_directional_light(u_directional_lights[i], material_sample, view_direction);
	
	for (int i = 0; i < u_point_light_count; i++) 
		result += calculate_point_light(u_point_lights[i], material_sample, view_direction);
	
	for (int i = 0; i < u_spot_light_count; i++) 
		result += calculate_spot_light(u_spot_lights[i], material_sample, view_direction);
	
	float gamma = 2.2;
	fragColor = vec4(pow(result, vec3(1.0 / gamma)), 1.0);
}
