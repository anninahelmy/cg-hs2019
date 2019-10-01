//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================

//== INCLUDES =================================================================

#include "Cylinder.h"
#include "SolveQuadratic.h"

#include <array>
#include <cmath>

//== IMPLEMENTATION =========================================================

bool

Cylinder::
intersect(const Ray&  _ray,
          vec3&       _intersection_point,
          vec3&       _intersection_normal,
          double&     _intersection_t) const
{
	const vec3& dir = _ray.direction;
	const vec3   oc = _ray.origin - center;

	std::array<double, 2> t;
	size_t nsol = solveQuadratic(dot(dir, dir) - dot(dir, axis) * dot(dir, axis),
		2 * (dot(dir, oc) - (dot(dir, axis) * dot(oc, axis))) ,
		dot(oc, oc) - (dot(oc, axis) * dot(oc, axis)) - radius * radius, t);

	_intersection_t = NO_INTERSECTION;

	// Find the closest valid solution (in front of the viewer) and check if intersection is with finite cylinder
	for (size_t i = 0; i < nsol; ++i) {
		if (t[i] <= 0) continue;
		double dist_cx = dot(t[i] * dir + oc, t[i] * dir + oc);
		if (dist_cx <= radius * radius + (height / 2) * (height / 2)) _intersection_t = std::min(_intersection_t, t[i]);
	}

	if (_intersection_t == NO_INTERSECTION) return false;

	// Compute intersection values
	_intersection_point = _ray(_intersection_t);
	vec3 cx = _intersection_point - center;
	_intersection_normal = ((dot(axis, cx) * axis) - cx) / radius;
	
	// Choose the orientation of the normal to be opposite to the ray's orientation if the ray intersects the surface inside.
	if (dot(_intersection_normal, dir) < 0)
		_intersection_normal *= -1.0;

	return true;    
}
