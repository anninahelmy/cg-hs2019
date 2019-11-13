//=============================================================================
//
//   Exercise code for "Introduction to Computer Graphics"
//     by Julian Panetta, EPFL
//
//=============================================================================
#version 140

// Eye-space fragment position and normals from vertex shader.
in vec3 v2f_normal;
in vec3 v2f_ec_vertex;

uniform vec3 light_position; // Eye-space light position
uniform vec3 light_color;

// Material parameters
uniform vec3  diffuse_color;
uniform vec3 specular_color;
uniform float shininess;

uniform samplerCube shadow_map; // Distances in the shadow map can be accessed with texture(shadow_map, direction).r

out vec4 f_light_contribution;

void main()
{
    // Orient the normal so it always points opposite the camera rays:
    vec3 N = -sign(dot(v2f_normal, v2f_ec_vertex)) *
             normalize(v2f_normal);

    /** \todo
    * Compute this light's diffuse and specular contributions.
    * You should be able to copy your phong lighting code from assignment 6 mostly as-is,
    * though notice that the light and view vectors need to be computed from scratch
    * here; this time, they are not passed from the vertex shader.
    *
    * The light should only contribute to this fragment if the fragment is not occluded
    * by another object in the scene. You need to check this by comparing the distance
    * from the fragment to the light against the distance recorded for this
    * light ray in the shadow map.
    *
    * To prevent "shadow acne" and minimize aliasing issues, we need a rather large
    * tolerance on the distance comparison. It's recommended to use a *multiplicative*
    * instead of additive tolerance: compare the fragment's distance to 1.01x the
    * distance from the shadow map.
    ***/
	 // Phong shading model: I = I_a * m_a + I_l * (m_d(n * l) + m_s(r*v)^s)

    vec3 color = vec3(0.0,0.0,0.0);
	vec3 vertexLight = - light_position + v2f_ec_vertex;
	vec3 v2f_light = normalize(-vertexLight);
	
	vec3 v2f_view = -normalize(v2f_ec_vertex);
	

	 // Add diffuse light and specular light
	if (length(vertexLight) < 1.01*texture(shadow_map, vertexLight).r) {
		float nl = dot(N, v2f_light);
		if (nl > 0) color += light_color * diffuse_color * nl;
		vec3 r = reflect(v2f_light, N);
		float rv = dot(v2f_view, r);
		if (nl > 0 && rv > 0) color += light_color * specular_color * pow(rv, shininess);

	}

    // append the required alpha value
    f_light_contribution = vec4(color, 1.0);
	//f_light_contribution = vec4(0.0025*texture(shadow_map, vertexLight).r, 0, 0, 1.f);
}
