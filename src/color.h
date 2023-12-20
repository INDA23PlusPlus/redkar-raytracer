#ifndef COLOR
#define COLOR

#include <iostream>
#include <random>
#include "vec3.h"
#include "ray.h"

using color3 = vec3;

mt19937 mt{random_device{}()};
uniform_int_distribution ud{0, 255};

void color_to_ppm(color3 pixel) {
	cout << static_cast<int>(255.999 *  pixel.x) << " "
	     << static_cast<int>(255.999 *  pixel.y) << " "
	     << static_cast<int>(255.999 *  pixel.z) << "\n";
}

bool sphere_intersection(const ray &r, const point3 &center, double radius) {
	// quadratic formula:
	// v = ray origin - sphere center, a = ray direction ^ 2, b = 2 * v * ray direction, c = v^2 - radius^2
	vec3 direction = r.dirVec;
	double epsilon = 1e-6;
	vec3 v = r.origin - center;
	double a = direction.dot(direction);
	double b = (2 * v).dot(direction);
	double c = v.dot(v) - radius * radius;
	double discriminant = b * b - 4.0 * a * c;
	return (discriminant >= epsilon);
	// we only need the discriminant since we don't care where it touches,
	// only that it does.
}


color3 ray_to_color(const ray &r) {
	if (sphere_intersection(r, point3(0, 0, -1), 0.3)) {
		return color3(0, 1, 0);
	}
	vec3 unit_direction = r.dirVec / r.dirVec.norm();
	//cerr << unit_direction.norm() << "\n";
	//auto a = 0.5*(unit_direction.y + 1.0);
	auto a = 0.7 * (unit_direction.y + 0.7);
   	//return (1.0-a)*color3(1.0, 1.0, 1.0) +  a*color3(0.5, 0.7, 1.0);
    	return (1.0-a)*color3(1.0, 1.0, 1.0) +  a*color3(0.0, 0.0, 1.0);
	//cerr << "1.0 - a: " << 1.0 - a << "\n";
	//cerr << "a: " << a << "\n";
	//assert(a < (1.0 -a));
	//return ((1.0 - a) > a ? color3(1.0, 0.0, 0.0) : color3(0.0, 0.0, 1.0));
}


#endif

