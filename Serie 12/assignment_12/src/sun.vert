//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout (location = 0) in vec4 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_texcoord;

out vec2 v2f_texcoord;
out vec3 v2f_origpos;

uniform mat4 modelview_projection_matrix;
uniform float t;    // Simulation time (for animating the sun)

void main()
{
    // pass through texture coordinate
    v2f_texcoord = v_texcoord;
    v2f_origpos = v_position.xyz;

    vec4 spos;
    float theta = acos(v_position.z);//0 to pi
    float sintheta = sin(3*theta + t);
    float phi = v_position.x/sin(theta);//0 to 2*pi
    float cosphi = cos(2*phi + 2*t);
    spos.xyz = v_position.xyz * (1.0 + 0.025*sintheta*cosphi);
    spos.w = 1.0;

    // transform vertex by modelview and projection matrix
    gl_Position = modelview_projection_matrix * spos;

}
