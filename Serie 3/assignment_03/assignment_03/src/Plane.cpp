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

#include "Plane.h"
#include <limits>


//== CLASS DEFINITION =========================================================



Plane::Plane(const vec3& _center, const vec3& _normal)
	: center(_center), normal(_normal)
{
}


//-----------------------------------------------------------------------------


bool
Plane::
intersect(const Ray& _ray,
	vec3& _intersection_point,
	vec3& _intersection_normal,
	double& _intersection_t) const
{
	const vec3 dir = _ray.direction;
	const vec3   oc = center - _ray.origin;

	const double nd_dotProduct = dot(normal, dir);

	// Find the closest valid solution (in front of the viewer)
	// If ray is parallel to plane consider it no intersection (ray in parallel to plane (no intersection)
	// or ray is in plane (no visible plane (1 pixel is not visible)). Else return intersection.
	if (nd_dotProduct == 0) _intersection_t = NO_INTERSECTION;
	else {
		_intersection_t = dot(normal, oc) / nd_dotProduct;
		if (_intersection_t < 0) _intersection_t = NO_INTERSECTION;
	}

	if (_intersection_t == NO_INTERSECTION) return false;

	_intersection_point = _ray(_intersection_t);
	_intersection_normal = normal;

	return true;
}


//=============================================================================
