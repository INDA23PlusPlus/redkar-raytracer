#ifndef COLOR
#define COLOR

#include <iostream>
#include <random>
#include "vec3.h"
#include "ray.h"
#include "object.h"

using color3 = vec3;

mt19937 mt{random_device{}()};
uniform_int_distribution ud{0, 255};

void color_to_ppm(color3 pixel) {
	cout << static_cast<int>(255.999 *  pixel.x) << " "
	     << static_cast<int>(255.999 *  pixel.y) << " "
	     << static_cast<int>(255.999 *  pixel.z) << "\n";
}


color3 ray_to_color(vector<sphere> &sphere_list, const ray &r) {

	// hard code the lightsource since there is only 1
	sphere light(point3(-0.77, 0.4, -1), 0.1, color3(1, 1, 1));

	/*
	bounceStats s1_bounce = s1.sphere_intersection(r);
	bounceStats light_bounce = light.sphere_intersection(r);
	
	if (light_bounce.happened) {
		//vec3 normal = normalize(r.loc(hit) - point3(0, 0, -1));
		vec3 light_normal = light_bounce.bouncePoint;
		//cerr << light_normal.x << " " << light_normal.y << " " << light_normal.z << "\n";
		//return 0.5 * color3(light_normal.x+1, light_normal.y+1, light_normal.z+1);
		return color3(1, 1, 1);
	}
	if (s1_bounce.happened) {
		//vec3 normal = normalize(r.loc(hit) - point3(0, 0, -1));
		vec3 s1_normal = s1_bounce.bouncePoint;
		//cerr << s1_normal.x << " " << s1_normal.y << " " << s1_normal.z << "\n";
		//return 0.5 * color3(s1_normal.x+1, s1_normal.y+1, s1_normal.z+1);
		return color3(0, 0, 0);
	}
	*/
	double minDist = 10000000000.0;
	bounceStats bst(false, 0.0, vec3(), vec3());
	sphere hitSphere(point3(1000.0, 1000.0, 1000.0), 100000.0, vec3());
	//cerr << "#objects: " << (int)sphere_list.size() << "\n";
	for(auto &ball: sphere_list) {
		bounceStats cur_bounce = ball.sphere_intersection(r);
		if (cur_bounce.happened && cur_bounce.rayTravelDist < minDist) {
			bst = cur_bounce;
			minDist = cur_bounce.rayTravelDist;
			hitSphere = ball;
		}
	}
	
	if (bst.happened) {
		//cerr << "I hit something" << "\n";
		return hitSphere.material;
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

