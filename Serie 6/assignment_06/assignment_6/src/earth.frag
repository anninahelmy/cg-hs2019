//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140

in vec3 v2f_normal;
in vec2 v2f_texcoord;
in vec3 v2f_light;
in vec3 v2f_view;

out vec4 f_color;

uniform sampler2D day_texture;
uniform sampler2D night_texture;
uniform sampler2D cloud_texture;
uniform sampler2D gloss_texture;
uniform bool greyscale;

const float shininess = 20.0;
const vec3  sunlight = vec3(1.0, 0.941, 0.898);

void main()
{
    /** \todo
        * - Copy your working code from the fragment shader of your Phong shader use it as
        * starting point
        * - instead of using a single texture, use the four texures `day_texure`, `night_texure`,
        * `cloud_texure` and `gloss_texture` and mix them for enhanced effects
        * Hints:
        * - cloud and gloss textures are just greyscales. So you'll just need one color-
        * component.
        * - The texture(texture, 2d_position) returns a 4-vector (rgba). You can use
        * `texture(...).r` to get just the red component or `texture(...).rgb` to get a vec3 color
        * value
        * - use mix(vec3 a,vec3 b, s) = a*(1-s) + b*s for linear interpolation of two colors
         */

    vec3 day_color = vec3(0.0,0.0,0.0);
    vec3 night_color = vec3(0.0,0.0,0.0);
    vec3 cloud_color = vec3(0.0,0.0,0.0);

    float cloud_greyscale = texture(cloud_texture, v2f_texcoord.st).r;


	vec3 m_ad = texture(day_texture, v2f_texcoord.st).rgb;
	vec3 m_ad_clouds = texture(cloud_texture, v2f_texcoord.st).rgb;
	vec3 I_a = 0.2f * sunlight;
	vec3 I_l = sunlight;


	// Add ambient light
	day_color += I_a * m_ad;
    cloud_color += I_a * m_ad_clouds;

    // Add diffuse light
    float n_dot_l = dot(v2f_normal, v2f_light);
	if (n_dot_l > 0) {
		day_color += I_l * m_ad * n_dot_l;
		cloud_color += I_l * m_ad_clouds * n_dot_l;
	}


	// Add specular light
	vec3 m_s = vec3(1,1,1);
	vec3 r = reflect(v2f_light, v2f_normal);
	float r_dot_v = dot(r, v2f_view);

	float specular_amount = texture(gloss_texture, v2f_texcoord.st).r * (1-cloud_greyscale);
	if (n_dot_l > 0 && r_dot_v > 0) {
    	day_color += specular_amount * I_l * m_s * pow(r_dot_v, shininess);
    }


    // Add clouds to main color
    day_color = mix(day_color, cloud_color, cloud_greyscale);


    night_color = (1-cloud_greyscale)*texture(night_texture, v2f_texcoord.st).rgb;


    vec3 color = mix(night_color, day_color, n_dot_l);

    // convert RGB color to YUV color and use only the luminance
    if (greyscale) color = vec3(0.299*color.r+0.587*color.g+0.114*color.b);

    // add required alpha value
    f_color = vec4(color, 1.0);
}
