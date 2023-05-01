#version 430

#define MAX_DIRECTIONAL_LIGHTS 1
#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS 4

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

struct Attenutaion {
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
	Attenutaion attenutaion;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

    LightProperties properties;
	Attenutaion attenutaion;
};

smooth in vec3 world_position;
smooth in vec3 normal;
smooth in vec2 UV;

uniform vec3 u_camera_position;

uniform DirectionalLight u_directional_lights[MAX_DIRECTIONAL_LIGHTS];
uniform int u_directional_light_count;
uniform PointLight u_point_lights[MAX_POINT_LIGHTS];
uniform int u_point_light_count;
uniform SpotLight u_spot_lights[MAX_SPOT_LIGHTS];
uniform int u_spot_light_count;

uniform Material u_material;

out vec4 fragColor;

MaterialSample sample_material() {
	MaterialSample result;
	result.diffuse = u_material.using_diffuse_map ? texture(u_material.diffuse_map, UV).xyz : u_material.diffuse;
	result.specular = u_material.using_specular_map ? texture(u_material.specular_map, UV).xyz : u_material.specular;
	result.shininess = u_material.shininess;
	result.normal = normalize(normal);

	return result;
}

vec3 phong(LightProperties light, MaterialSample material, vec3 view_direction, vec3 light_direction) {
	vec3 ambient = light.ambient * material.diffuse;

	float visibility = max(dot(material.normal, -light_direction), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * visibility;

	#ifdef BLINN
	vec3 half_direction = normalize(view_direction + light_direction);
	vec3 specular = light.specular * material.specular * pow(max(dot(material.normal, half_direction), 0.0), material.shininess) * visibility;
	#else
	vec3 reflect_direction = reflect(light_direction, material.normal);
	vec3 specular = light.specular * material.specular * pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess) * visibility;
	#endif

	return ambient + diffuse + specular;
}

vec3 calculate_directional_light(DirectionalLight light, MaterialSample material, vec3 view_direction) {
	return phong(light.properties, material, view_direction, normalize(light.direction));
}

vec3 calculate_point_light(PointLight light, MaterialSample material, vec3 view_direction) {
	vec3 light_direction = normalize(light.position - world_position);

	float distance = length(light.position - world_position);
	float attenuation = 1.0 / (light.attenutaion.constant + light.attenutaion.linear * distance + light.attenutaion.quadratic * (distance * distance));

	return phong(light.properties, material, view_direction, light_direction) * attenuation;
}

vec3 calculate_spot_light(SpotLight light, MaterialSample material, vec3 view_direction) {
	vec3 light_direction = normalize(light.position - world_position);

	float distance = length(light.position - world_position);
	float attenuation = 1.0 / (light.attenutaion.constant + light.attenutaion.linear * distance + light.attenutaion.quadratic * (distance * distance));

	float theta = dot(light_direction, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	return phong(light.properties, material, view_direction, light_direction) * attenuation * intensity;
}

void main() {
	vec3 view_direction = normalize(u_camera_position - world_position);
	MaterialSample material_sample = sample_material();

	vec3 result = vec3(0.0);

	for (int i = 0; i < u_directional_light_count; i++) 
		result += calculate_directional_light(u_directional_lights[i], material_sample, view_direction);
	
	for (int i = 0; i < u_point_light_count; i++) 
		result += calculate_point_light(u_point_lights[i], material_sample, view_direction);
	
	for (int i = 0; i < u_spot_light_count; i++) 
		result += calculate_spot_light(u_spot_lights[i], material_sample, view_direction);
 
	fragColor = vec4(result, 1.0);
}
