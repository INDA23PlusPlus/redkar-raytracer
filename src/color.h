#ifndef COLOR
#define COLOR

#include <iostream>
#include "vec3.h"

using color = vec3;

void color_to_ppm(color pixel) {
	cout << static_cast<int>(255.999 * pixel.x) << " "
	     << static_cast<int>(255.999 * pixel.y) << " "
	     << static_cast<int>(255.999 * pixel.z) << "\n";
}

#endif

