#ifndef RAY
#define RAY

#include "vec3.h"

class ray {
public:
	point3 origin;
	vec3 dirVec;

	ray(const vec3 &origin, const vec3 &dirVec): origin(origin), dirVec(dirVec) {}

	point3 loc(double t) const {
		return origin + t*dirVec;
	}

};

#endif
