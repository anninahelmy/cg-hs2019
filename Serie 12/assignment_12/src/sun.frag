//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140

in  vec2 v2f_texcoord;
in  vec3 v2f_origpos;
out vec4 f_color;

uniform sampler2D tex;
uniform bool greyscale;
uniform bool do_sun_tricks;
uniform float t;


void main()
{
    vec3 opos = normalize(v2f_origpos);
    float theta = acos(opos.z);//0 to pi
    float sintheta = sin(3*theta + t);
    float phi = opos.x/sin(theta);//0 to 2*pi
    float cosphi = cos(2*phi + 2*t);

    vec2 texcoord = v2f_texcoord.st;
    if (do_sun_tricks) {
        texcoord += 0.02 * vec2(sintheta, cosphi);
    }
    // fetch color (rgb and alpha) from texture
    vec4 color = texture(tex, texcoord);

    // For greyscale mode, convert RGB color to YUV and use only the luminance
    if (greyscale) color.rgb = vec3(0.299 * color.r
                                  + 0.587 * color.g
                                  + 0.114 * color.b);

    f_color = color;
}
