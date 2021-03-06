#include "Mesh.h"
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

#include "Mesh.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <limits>
#include <cmath>


//== IMPLEMENTATION ===========================================================


Mesh::Mesh(std::istream &is, const std::string &scenePath)
{
    std::string meshFile, mode;
    is >> meshFile;

    const char pathSep =
#ifdef _WIN32
                            '\\';
#else
                            '/';
#endif

    // load mesh from file
    read(scenePath.substr(0, scenePath.find_last_of(pathSep) + 1) + meshFile);

    is >> mode;
    if      (mode ==  "FLAT") draw_mode_ = FLAT;
    else if (mode == "PHONG") draw_mode_ = PHONG;
    else throw std::runtime_error("Invalid draw mode " + mode);

    is >> material;
}


//-----------------------------------------------------------------------------


bool Mesh::read(const std::string &_filename)
{
    // read a mesh in OFF format


    // open file
    std::ifstream ifs(_filename);
    if (!ifs)
    {
        std::cerr << "Can't open " << _filename << "\n";
        return false;
    }


    // read OFF header
    std::string s;
    unsigned int nV, nF, dummy, i;
    ifs >> s;
    if (s != "OFF")
    {
        std::cerr << "No OFF file\n";
        return false;
    }
    ifs >> nV >> nF >> dummy;
    std::cout << "\n  read " << _filename << ": " << nV << " vertices, " << nF << " triangles";


    // read vertices
    Vertex v;
    vertices_.clear();
    vertices_.reserve(nV);
    for (i=0; i<nV; ++i)
    {
        ifs >> v.position;
        vertices_.push_back(v);
    }


    // read triangles
    Triangle t;
    triangles_.clear();
    triangles_.reserve(nF);
    for (i=0; i<nF; ++i)
    {
        ifs >> dummy >> t.i0 >> t.i1 >> t.i2;
        triangles_.push_back(t);
    }


    // close file
    ifs.close();


    // compute face and vertex normals
    compute_normals();

    // compute bounding box
    compute_bounding_box();


    return true;
}


//-----------------------------------------------------------------------------

// Determine the weights by which to scale triangle (p0, p1, p2)'s normal when
// accumulating the vertex normals for vertices 0, 1, and 2.
// (Recall, vertex normals are a weighted average of their incident triangles'
// normals, and in our raytracer we'll use the incident angles as weights.)
// \param[in] p0, p1, p2    triangle vertex positions
// \param[out] w0, w1, w2    weights to be used for vertices 0, 1, and 2
void angleWeights(const vec3 &p0, const vec3 &p1, const vec3 &p2,
                  double &w0, double &w1, double &w2) {
    // compute angle weights
    const vec3 e01 = normalize(p1-p0);
    const vec3 e12 = normalize(p2-p1);
    const vec3 e20 = normalize(p0-p2);
    w0 = acos( std::max(-1.0, std::min(1.0, dot(e01, -e20) )));
    w1 = acos( std::max(-1.0, std::min(1.0, dot(e12, -e01) )));
    w2 = acos( std::max(-1.0, std::min(1.0, dot(e20, -e12) )));
}


//-----------------------------------------------------------------------------

void Mesh::compute_normals()
{
    // compute triangle normals
    for (Triangle& t: triangles_)
    {
        const vec3& p0 = vertices_[t.i0].position;
        const vec3& p1 = vertices_[t.i1].position;
        const vec3& p2 = vertices_[t.i2].position;
        t.normal = normalize(cross(p1-p0, p2-p0));
    }

    // initialize vertex normals to zero
    for (Vertex& v: vertices_)
    {
        v.normal = vec3(0,0,0);
    }

	for (Triangle& t : triangles_)
	{
		const vec3& p0 = vertices_[t.i0].position;
		const vec3& p1 = vertices_[t.i1].position;
		const vec3& p2 = vertices_[t.i2].position;

		double w0, w1, w2;

		// Weigh the normals by their triangles' angles.
		angleWeights(p0, p1, p2, w0, w1, w2);

		//adding the normals all together
		vertices_[t.i0].normal += t.normal * w0;
		vertices_[t.i1].normal += t.normal * w1;
		vertices_[t.i2].normal += t.normal * w2;
	}

	for (Vertex& v : vertices_)
	{
		v.normal = normalize(v.normal);
	}

    /** \todo
     * In some scenes (e.g the office scene) some objects should be flat
     * shaded (e.g. the desk) while other objects should be Phong shaded to appear
     * realistic (e.g. chairs). You have to implement the following:
     * - Compute vertex normals by averaging the normals of their incident triangles.
     * - Store the vertex normals in the Vertex::normal member variable.
     * - Weigh the normals by their triangles' angles.
     */
}


//-----------------------------------------------------------------------------


void Mesh::compute_bounding_box()
{
    bb_min_ = vec3(std::numeric_limits<double>::max());
    bb_max_ = vec3(std::numeric_limits<double>::lowest());

    for (Vertex v: vertices_)
    {
        bb_min_ = min(bb_min_, v.position);
        bb_max_ = max(bb_max_, v.position);
    }
}


//-----------------------------------------------------------------------------


// Intersect the ray `_ray` with the axis-aligned bounding box of the mesh. Return whether the ray intersects the bounding box.
bool Mesh::intersect_bounding_box(const Ray& _ray) const
{
	for (int i = 0; i < 3; i++)
	{
		if (intersect_box_side(_ray, i, bb_min_[i]) || intersect_box_side(_ray, i, bb_max_[i])) return true;
	}

    return false;
}

bool Mesh::intersect_box_side(const Ray& _ray, int axis, double plane) const
{
	double t = (plane - _ray.origin[axis]) / _ray.direction[axis];
	vec3 intersection_point = _ray(t);
	
	// Check for all axis but given one if plane intersection is within rectangle.
	for (int i = (axis + 1) % 3; i != axis; i = (i + 1) % 3)
	{
		if (intersection_point[i] > bb_max_[i] || intersection_point[i] < bb_min_[i]) return false;
	}

	return true;
}

//-----------------------------------------------------------------------------


bool Mesh::intersect(const Ray& _ray,
                     vec3&      _intersection_point,
                     vec3&      _intersection_normal,
                     double&    _intersection_t ) const
{
    // check bounding box intersection
    if (!intersect_bounding_box(_ray))
    {
        return false;
    }

    vec3   p, n;
    double t;

    _intersection_t = NO_INTERSECTION;

    // for each triangle
    for (const Triangle& triangle : triangles_)
    {
        // does ray intersect triangle?
        if (intersect_triangle(triangle, _ray, p, n, t))
        {
            // is intersection closer than previous intersections?
            if (t < _intersection_t)
            {
                // store data of this intersection
                _intersection_t      = t;
                _intersection_point  = p;
                _intersection_normal = n;
            }
        }
    }

    return (_intersection_t != NO_INTERSECTION);
}


//-----------------------------------------------------------------------------


bool
Mesh::
intersect_triangle(const Triangle&  _triangle,
                   const Ray&       _ray,
                   vec3&            _intersection_point,
                   vec3&            _intersection_normal,
                   double&          _intersection_t) const
{
    const vec3& p0 = vertices_[_triangle.i0].position;
    const vec3& p1 = vertices_[_triangle.i1].position;
    const vec3& p2 = vertices_[_triangle.i2].position;

    /** \todo
    * - intersect _ray with _triangle
    * - store intersection point in `_intersection_point`
    * - store ray parameter in `_intersection_t`
    * - store normal at intersection point in `_intersection_normal`.
    * - Depending on the member variable `draw_mode_`, use either the triangle
    *  normal (`Triangle::normal`) or interpolate the vertex normals (`Vertex::normal`).
    * - return `true` if there is an intersection with t > 0 (in front of the viewer)
    *
    * Hint: Rearrange `ray.origin + t*ray.dir = a*p0 + b*p1 + (1-a-b)*p2` to obtain a solvable
    * system for a, b and t.
    * Refer to [Cramer's Rule](https://en.wikipedia.org/wiki/Cramer%27s_rule) to easily solve it.
     */

	//intersect _ray with _triangle by solving the equation o + dt = alpha*A + beta*B + gamma*C.
	//By subset gamma with (1-alpha-beta) we get o - c = alpha * (a - c) + beta * ( b - c ) - t * d.
	double main_det, x_det, y_det, z_det;
	double alpha, beta, gamma;
	
	vec3 dir = _ray.direction;
	vec3 origin = _ray.origin;

	main_det = calculate_det(p0 - p2, p1 - p2, -dir);
	x_det = calculate_det(origin - p2, p1 - p2, -dir);
	y_det = calculate_det(p0 - p2, origin - p2, -dir);
	z_det = calculate_det(p0 - p2, p1 - p2, origin - p2);

	// If main_det = 0 then we have no intersection or infinitely many intersections (ray lies in triangle plane). In both cases we see nothing.
	if (main_det == 0) return false;

	alpha = x_det / main_det;
	beta = y_det / main_det;
	gamma = 1 - alpha - beta;
	_intersection_t = z_det / main_det;

	// Check if alpha, beta, gamma > 0, to get an intersection within the triangle.
	if ( alpha < 0 || beta < 0 || gamma < 0 || _intersection_t < 0) return false;

	_intersection_point = _ray(_intersection_t);

	// if objects are flat shaded the intersection normal is the normal of the intersected triangle
	if (draw_mode_ == FLAT)
	{
		_intersection_normal = _triangle.normal;
	}
	//if objects are phong shaded we need to use the interpolate vertex normals (with formula n(x) = alpha*n(p0)+beta*n(p1)+gamma*n(p2)
	else
	{
		const vec3& v0 = vertices_[_triangle.i0].normal;
		const vec3& v1 = vertices_[_triangle.i1].normal;
		const vec3& v2 = vertices_[_triangle.i2].normal;

		const vec3& nx = alpha * v0 + beta * v1 + gamma * v2;
		_intersection_normal = normalize(nx);
	}

	return true;
}

static double calculate_det(vec3 _a, vec3 _b, vec3 _c)
{
	return _a[0] * _b[1] * _c[2] + _a[1] * _b[2] * _c[0] + _a[2] * _b[0] * _c[1]
		- (_a[2] * _b[1] * _c[0] + _a[0] * _b[2] * _c[1] + _a[1] * _b[0] * _c[2]);
}


//=============================================================================
