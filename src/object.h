#ifndef SPHERE
#define SPHERE

#include <random>
#include "vec3.h"
#include "ray.h"
#include "color.h"

struct bounceStats {
	bool happened;
	double rayTravelDist;
	point3 bouncePoint;
	vec3 normal;
	bounceStats(bool h, double rtd, point3 bp, vec3 n): happened(h), rayTravelDist(rtd), bouncePoint(bp), normal(n) {}
};

struct sphere {
	point3 center;
	double radius;
	color3 material;
	double reflectance;

	sphere(point3 c, double r, color3 m, double rf): center(c), radius(r), material(m), reflectance(rf) {}

	bounceStats sphere_intersection(const ray &r) {
		// quadratic formula:
		// v = ray origin - sphere center, a = ray direction ^ 2, b = 2 * v * ray direction, c = v^2 - radius^2
		vec3 direction = r.dirVec;
		double epsilon = 1e-6;
		vec3 v = r.origin - center;
		double a = direction.dot(direction);
		double b = (2 * v).dot(direction);
		double c = v.dot(v) - radius * radius;
		double discriminant = b * b - 4.0 * a * c;

		if (discriminant < epsilon) {
			return bounceStats{false, 0.0, vec3(), vec3()};
		}
		else {
			double t = (-b - sqrt(discriminant)) / (2.0 * a);
			vec3 travelRay = t * direction;
			double rayTravelDist = travelRay.norm();
			point3 bouncePoint = r.loc(t);
			vec3 normal = normalize(bouncePoint - center);
			if (rayTravelDist < epsilon) {
				return bounceStats{false, 0.0, vec3(), vec3()};
			}
			return bounceStats{true, rayTravelDist, bouncePoint, normal};
		}
		
		//return (discriminant >= epsilon);
		// we only need the discriminant since we don't care where it touches,
		// only that it does.
	}
		
};



#endif

