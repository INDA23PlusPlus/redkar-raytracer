#include <iostream>
#include "vec3.h"
#include "color.h"

using namespace std; // I stan using this 

int main() {

	double ideal_dimensions = 16.0 / 9.0;
	int window_width = 500; // basically the pixels
	int window_height = window_width / ideal_dimensions;
	if (window_height == 0) window_height++;

	
	
	// eye and projector
	point3 eye = point3(0, 0, 0);
	double projector_width = 5.0;
	double projector_height = projector_width / ( (double)(image_width) / (double) (image_height) )
	double eye_to_projector_dist = 1.0;

	vec3 x_edge = vec3(projector_width, 0, 0);
	vec3 y_edge = vec3(0, -projector_height, 0);
	
	vec3 dx = x_edge / (double) window_width;
	vec3 dy = y_edge / (double) window_height;

	// Render

	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (int j = 0; j < height; ++j) {
        	std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        	for (int i = 0; i < width; ++i) {
			vec3 pixel = color(double(i)/(width-1), double(j)/(height-1), 0);
			color_to_ppm(pixel);
        	}
    	}

    	std::clog << "\rDone.                 \n";

}
