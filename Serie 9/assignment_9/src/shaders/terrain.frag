//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140

uniform vec3 light_position; // Eye-space light position

in vec3  v2f_ec_vertex;
in vec3  v2f_normal;
in float v2f_height;

out vec4 f_color;

const vec3  sunlight = vec3(1.0, 0.941, 0.898);
// Small perturbation to prevent "z-fighting" on the water on some machines...
const float terrain_water_level    = -0.03125 + 1e-6;
const vec3  terrain_color_water    = vec3(0.29, 0.51, 0.62);
const vec3  terrain_color_mountain = vec3(0.8, 0.5, 0.4);
const vec3  terrain_color_grass    = vec3(0.33, 0.43, 0.18);

void main()
{
	const vec3 ambient = 0.2 * sunlight; // Ambient light intensity
	float height = v2f_height;

    /**
	 * \todo Compute the terrain color ("material") and shininess based on the height as
	 * described in the handout.
	 *
	 * Water:
	 *		color = terrain_color_water
	 *		shininess = 8.0
	 * Ground:
	 *		color = interpolate between terrain_color_grass and terrain_color_mountain, weight is (height - terrain_water_level)*2
	 * 		shininess = 0.5
     */

		 //terrain color
		vec3 material;
	 	float shininess;

	 	if (height > terrain_water_level) {
	 		material = mix(terrain_color_grass, terrain_color_mountain, (height - terrain_water_level)*2);
	 		shininess = 0.5;
	 	} else {
	 		material = terrain_color_water;
	 		shininess = 8.0;
	 	}

    /**
	 * \todo Paste your Phong fragment shading code from assignment 6/7 here,
	 * altering it to use the terrain color as the ambient, diffuse, and
	 * specular materials.
     */

	 	vec3 light_ray = v2f_ec_vertex - light_position;

		//phong: Ia*ma + Il*md(nl*l) + Il*ms(r*v)^s
		
		vec3 color = vec3(0.0, 0.0, 0.0);

		//add ambient light
		color += ambient * material;
		// normalize normal, light, reflected ligth and view vector

	 	vec3 normal = normalize(v2f_normal);
	 	vec3 light = normalize(-light_ray);
	 	vec3 view = normalize(-v2f_ec_vertex);
	 	vec3 reflected = normalize(reflect(-light, normal));

	 	// diffuse and specular contributions (use the same material color for both)
		
	 	float nl  = dot(normal, light);
	 	float rv = dot(view, reflected);

		if (nl > 0) color += nl * material * sunlight;
		if(nl > 0 && rv > 0) color += pow(dot(reflected, view), shininess) * material * sunlight;

		f_color = vec4(color, 1.0); //alpha value
}
