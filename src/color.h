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
	//sphere light(point3(-0.77, 0.4, -1), 0.1, color3(1, 1, 1), 1.0);

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

	ray cur_ray = r;
	color3 ray_color(1, 1, 1);
	color3 gathered_light(0, 0, 0);
	bool hitSomething = false;
	double global_minDist = 100000000000.0;

	for(int i = 0; i < 6; i++) {
		double minDist = 10000000000.0;
		sphere hitSphere(point3(1000.0, 1000.0, 1000.0), 100000.0, vec3(), 0, vec3());
		bounceStats bst(false, 0.0, vec3(), vec3());

		for(auto &ball: sphere_list) {
			bounceStats cur_bounce = ball.sphere_intersection(cur_ray);
			if (cur_bounce.happened && cur_bounce.rayTravelDist < minDist) {
				bst = cur_bounce;
				minDist = cur_bounce.rayTravelDist;
				hitSphere = ball;
			}
		}

		if (i == 0) global_minDist = min(minDist, global_minDist);

		if (bst.happened) {
			hitSomething = true;
			//cerr << "I hit something" << "\n";
			//return hitSphere.material;
			cur_ray.origin = bst.bouncePoint;
			cur_ray.dirVec = random_vector();
			//cerr << "cur_ray.dirVec: " << cur_ray.dirVec.x << " " << cur_ray.dirVec.y << " " << cur_ray.dirVec.z << "\n";
			if (cur_ray.dirVec.dot(bst.normal) < 0) {
				cur_ray.dirVec = -1 * cur_ray.dirVec;
			}
			
			color3 emittedLight = hitSphere.reflectance * hitSphere.emittedColor; 
			double angle_adjustment = bst.normal.dot(cur_ray.dirVec);
			//cerr << "adjustment: " << angle_adjustment << "\n";
			gathered_light += emittedLight * ray_color;
			//ray_color = ray_color * hitSphere.material;
			ray_color = ray_color * hitSphere.material * angle_adjustment * 2;
			//cerr << "emittedLight: " << emittedLight.x << " " << emittedLight.y << " " << emittedLight.z << "\n";
			//cerr << ray_color.x << " " << ray_color.y << " " << ray_color.z << "\n";
			//cerr << "gathered light: " << gathered_light.x << " " << gathered_light.y << " " << gathered_light.z << "\n";
		}
		else {
			break;
		}
	}
	
	if (hitSomething) {
		if (gathered_light.x > 1) gathered_light.x = 1;
		if (gathered_light.y > 1) gathered_light.y = 1;
		if (gathered_light.z > 1) gathered_light.z = 1;
		return gathered_light;
	}

	triangle tri(point3(-0.6, 0.45, -1), point3(-0.6, 0.25, -1), point3(-0.5, 0.15, -1));
	cur_ray = r;
	bounceStats triangleBounce = tri.triangle_intersection(cur_ray);
	// TODO: fix the minDist problem
	if (triangleBounce.happened && triangleBounce.rayTravelDist < global_minDist) {
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

