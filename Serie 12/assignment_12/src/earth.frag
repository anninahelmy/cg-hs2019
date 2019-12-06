//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140

in vec3 v2f_raw_normal;
in vec3 v2f_normal;
in vec2 v2f_texcoord;
in vec3 v2f_light;
in vec3 v2f_view;
in vec3 v2f_tangent;
in vec3 v2f_bitangent;

out vec4 f_color;

uniform sampler2D day_texture;
uniform sampler2D night_texture;
uniform sampler2D cloud_texture;
uniform sampler2D gloss_texture;
uniform sampler2D normal_texture;
uniform bool greyscale;
uniform bool use_ambient_light;
uniform float t;
uniform mat3 normal_matrix;

uniform bool use_normal_mapping;

const float shininess = 20.0;
const vec3  sunlight = vec3(1.0, 0.941, 0.898);

void main()
{
    vec3 sphere_normal = normalize(v2f_normal);
    vec3 N;
    if (use_normal_mapping) {
        vec3 ntex = 2.0 * texture(normal_texture, v2f_texcoord.st).rgb - vec3(1.0, 1.0, 1.0);
        vec3 normal_objcoords = normalize(ntex.r * normalize(v2f_tangent)
                                    + ntex.g * normalize(v2f_bitangent)
                                    + ntex.b * normalize(v2f_raw_normal));

        N = normalize(normal_matrix * normal_objcoords);
    } else {
        N = sphere_normal;
    }

    // normalize directions
    vec3 L = normalize(v2f_light);
    vec3 V = normalize(v2f_view);
    vec3 R = normalize(reflect(-L, N));

    // compute diffuse and specular intensities
    float diffuse  = max(0.0, dot(N,L));
    float specular = (diffuse != 0.0) ? pow(max(0.0, dot(V,R)), shininess) : 0.0;

    vec2 cloud_motion = vec2(-0.01 * t,0);
    // fetch textures
    vec3  day   = texture(day_texture,    v2f_texcoord.st).rgb;
    vec3  night = texture(night_texture,  v2f_texcoord.st).rgb;
    float cloudiness = texture(cloud_texture,  v2f_texcoord.st + cloud_motion).r;
    float gloss = texture(gloss_texture,  v2f_texcoord.st).r;


    // clouds are not specular
    gloss *= (1.0 - cloudiness);


    float ambient = use_ambient_light ? 0.2 : 0.0;
    // combine textures with lighting following the Phong lighting model (specular material component is [1, 1, 1])
    day = ambient * sunlight * day + diffuse * sunlight * day + specular * gloss * sunlight;
    day = mix(day, ambient * sunlight * vec3(cloudiness) + diffuse * sunlight * vec3(cloudiness), cloudiness);
    night *= (1.0 - cloudiness);

    // mix day and night based on diffuse dot product

    float day_amount = clamp(2.0 * dot(sphere_normal,L), 0.0, 1.0);
    vec3 color = mix(night, day, day_amount);


    // convert RGB color to YUV color and use only the luminance
    if (greyscale) color = vec3(0.299*color.r+0.587*color.g+0.114*color.b);


    // add required alpha value
    f_color = vec4(color, 1.0);

}
