#include <iostream>
#include <cassert>
#include "vec3.h"
#include "color.h"
#include "ray.h"

using namespace std; // I stan using this 

int main() {

	double ideal_dimensions = 16.0 / 9.0;
	int window_width = 1280; // basically the pixels
	int window_height = window_width / ideal_dimensions;
	if (window_height == 0) window_height++;
	
	// eye and projector
	point3 eye = point3(0, 0, 0);
	double projector_width = 1.0;
	double projector_height = projector_width / ( (double)(window_width) / (double) (window_height) );
	double eye_to_projector_dist = 0.5;

	vec3 x_edge = vec3(projector_width, 0, 0);
	vec3 y_edge = vec3(0, -projector_height, 0);
	
	vec3 dx = x_edge / (double) window_width;
	vec3 dy = y_edge / (double) window_height;

	point3 top_left_corner = eye - vec3(0, 0, eye_to_projector_dist) - x_edge/2.0 - y_edge/2.0;	
	//point3 first_pixel = top_left_corner + dx/2 + dy/2;
	//point3 first_pixel = top_left_corner + dx/2.0 + dy/2.0;
	//point3 first_pixel = top_left_corner + 0.5 * dx + 0.5 * dy;
	point3 first_pixel = top_left_corner + 0.5*(dx + dy);
	cerr << "top left : " << first_pixel.x << " " << first_pixel.y << " " << first_pixel.z << "\n";

	// Render
	//cerr << "spaces: " << x_edge.norm() / dx.norm() << "\n";

	std::cout << "P3\n" << window_width << ' ' << window_height << "\n255\n";
	
	int point_cnt = 0;

	for (int j = 0; j < window_height; j++) {
        	//std::clog << "\rScanlines remaining: " << (window_height - j) << ' ' << std::flush;
        	for (int i = 0; i < window_width; i++) {
			point3 cur_pixel = first_pixel + (dy * j) + (dx * i);
			vec3 ray_dir = cur_pixel - eye;
			if (i == 0 && j == 0) cerr << "(0, 0) y is : " << ray_dir.y << "\n";
			if (i == window_width-1 && j == window_height-1) cerr << "(window, window) y is : " << ray_dir.y << "\n";
			ray cur_ray(eye, ray_dir);			

			point_cnt++;

			color3 pixel = ray_to_color(cur_ray);

			//vec3 pixel = color(double(i)/(width-1), double(j)/(height-1), 0);
			color_to_ppm(pixel);
        	}
    	}

	//assert(point_cnt == (window_width-1) * (window_height-1));

    	std::clog << "\rDone.                 \n";

}
