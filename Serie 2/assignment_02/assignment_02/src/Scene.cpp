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
#include "Scene.h"

#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Mesh.h"

#include <limits>
#include <map>
#include <functional>
#include <stdexcept>

#ifdef _OPENMP
#  include <omp.h>
#endif

//-----------------------------------------------------------------------------


Image Scene::render()
{
	// allocate new image.
	Image img(camera.width, camera.height);

	// Function rendering a full column of the image
	auto raytraceColumn = [&img, this](int x) {
		for (int y = 0; y<int(camera.height); ++y)
		{
			Ray ray = camera.primary_ray(x, y);

			// compute color by tracing this ray
			vec3 color = trace(ray, 0);

			// avoid over-saturation
			color = min(color, vec3(1, 1, 1));

			// store pixel color
			img(x, y) = color;
		}
	};

	// If possible, raytrace image columns in parallel.
	//
	// Mac users beware:
	// XCode's compiler (based on clang) does not support OpenMP
	// - you will have to install a vanialla clang (or gcc) if you want to use
	// OpenMP parallelization, e.g. via MacPorts.

#ifdef _OPENMP
	std::cout << "Rendering with up to " << omp_get_max_threads() << " threads." << std::endl;
#  pragma omp parallel for
#else
	std::cout << "Rendering singlethreaded." << std::endl;
#endif
	for (int x = 0; x<int(camera.width); ++x)
		raytraceColumn(x);

	// Note: compiler will elide copy.
	return img;
}

//-----------------------------------------------------------------------------

vec3 Scene::trace(const Ray& _ray, int _depth)
{
	// stop if recursion depth (=number of reflection) is too large
	if (_depth > max_depth) return vec3(0, 0, 0);

	// Find first intersection with an object. If an intersection is found,
	// it is stored in object, point, normal, and t.
	Object_ptr  object;
	vec3        point;
	vec3        normal;
	double      t;
	if (!intersect(_ray, object, point, normal, t))
	{
		return background;
	}

	// compute local Phong lighting (ambient+diffuse+specular)
	vec3 color = lighting(point, normal, -_ray.direction, object->material);

	
	/** \todo
	 * Compute reflections by recursive ray tracing:
	 * - check whether `object` is reflective by checking its `material.mirror`
	 * - check recursion depth
	 * - generate reflected ray, compute its color contribution, and mix it with
	 * the color computed by local Phong lighting (use `object->material.mirror` as weight)
	 * - check whether your recursive algorithm reflects the ray `max_depth` times
	 */

	return color;
}

//-----------------------------------------------------------------------------

bool Scene::intersect(const Ray& _ray, Object_ptr& _object, vec3& _point, vec3& _normal, double& _t)
{
	double  t, tmin(Object::NO_INTERSECTION);
	vec3    p, n;

	for (const auto& o : objects) // for each object
	{
		if (o->intersect(_ray, p, n, t)) // does ray intersect object?
		{
			if (t < tmin) // is intersection point the currently closest one?
			{
				tmin = t;
				_object = o.get();
				_point = p;
				_normal = n;
				_t = t;
			}
		}
	}

	return (tmin != Object::NO_INTERSECTION);
}

vec3 Scene::lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material)
{

	/* TODO: 
	* - only add diffuse and specular light if object is not in shadow
	*
	* You can look at the classes `Light` and `Material` to check their attributes. Feel free to use
	* the existing vector functions in vec3.h e.g. mirror, reflect, norm, dot, normalize
	*/

	//Phong lightning

	//ambient contribution
	vec3 ambient = _material.ambient * this->ambience;

	//diffuse and specular contribution
	vec3 diffuse = vec3(0, 0, 0);
	vec3 specular = vec3(0, 0, 0);

	//variables for intersection
	Object_ptr  object;
	vec3        point, normal;
	double      t;

	//compute intensity of light source for diffuse and specular contribution (with shadow)
	for (Light light : lights) {
		// Compute the shadow ray, the origin is the intersection point but since
		// it's needed to send the shadow ray from a displaced intersection point
		// to the light source, add a little bit (0.000001) of the direction vector

		Ray shadow;

		//direction of the shadow is from the intersection point to the light source
		shadow.direction = normalize(light.position - _point);
		shadow.origin = _point + 0.000001 * shadow.direction;

		//boolean to figure out if an intersection happens (shadow hits object and only ambient contribution is visible)
		bool intersection = intersect(shadow, object, point, normal, t);

		if (!intersection && t < distance(light.position, _point)) {

			double nl = dot(normalize(_normal), normalize((light.position - _point)));
			if (nl > 0) diffuse += light.color * nl * _material.diffuse;

			double rv = dot(2 * normalize(_normal) * nl - (normalize(light.position - _point)), _view);
			if (nl > 0 && rv > 0) specular += light.color * _material.specular * pow(rv, _material.shininess);
		}
	}


	vec3 color = ambient + diffuse + specular;

	//OLD:  visualize the normal as a RGB color for now.
	//vec3 color = (_normal + vec3(1)) / 2.0;

	return color;
}

//-----------------------------------------------------------------------------

void Scene::read(const std::string& _filename)
{
	std::ifstream ifs(_filename);
	if (!ifs)
		throw std::runtime_error("Cannot open file " + _filename);

	const std::map<std::string, std::function<void(void)>> entityParser = {
		{"depth",      [&]() { ifs >> max_depth; }},
		{"camera",     [&]() { ifs >> camera; }},
		{"background", [&]() { ifs >> background; }},
		{"ambience",   [&]() { ifs >> ambience; }},
		{"light",      [&]() { lights.emplace_back(ifs); }},
		{"plane",      [&]() { objects.emplace_back(new    Plane(ifs)); }},
		{"sphere",     [&]() { objects.emplace_back(new   Sphere(ifs)); }},
		{"cylinder",   [&]() { objects.emplace_back(new Cylinder(ifs)); }},
		{"mesh",       [&]() { objects.emplace_back(new     Mesh(ifs, _filename)); }}
	};

	// parse file
	std::string token;
	while (ifs && (ifs >> token) && (!ifs.eof())) {
		if (token[0] == '#') {
			ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (entityParser.count(token) == 0)
			throw std::runtime_error("Invalid token encountered: " + token);
		entityParser.at(token)();
	}
}


//=============================================================================
