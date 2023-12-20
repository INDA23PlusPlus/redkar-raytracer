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

/*
color3 ray_to_color(const ray &r) {
	return color3(ud(mt), ud(mt), ud(mt));
}
*/
color3 ray_to_color(const ray &r) {
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

