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
layout (location = 3) in vec3 v_tangent;
layout (location = 4) in vec3 v_bitangent;

out vec3 v2f_raw_normal;
out vec3 v2f_normal;
out vec3 v2f_light;
out vec3 v2f_view;
out vec2 v2f_texcoord;
out vec3 v2f_tangent;
out vec3 v2f_bitangent;

uniform mat4 modelview_projection_matrix;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform vec4 light_position; //in eye space coordinates already



void main()
{

    // vertex & light in eye coordinates
    vec3 ec_vertex = (modelview_matrix * v_position).xyz;
    vec3 ec_light  = (light_position).xyz;

    // transform normal to eye coordinates
    v2f_normal = normalize(normal_matrix * v_normal);
    v2f_raw_normal = v_normal;

    // direction to light source
    v2f_light = normalize(ec_light - ec_vertex);

    // viewing vector (from eye to vertex in view coordinates)
    v2f_view = normalize(-ec_vertex.xyz);

    // pass through texture coordinate
    v2f_texcoord = v_texcoord;

    v2f_tangent = v_tangent;
    v2f_bitangent = v_bitangent;

    // transform vertex by modelview and projection matrix
    gl_Position = modelview_projection_matrix * v_position;

}
