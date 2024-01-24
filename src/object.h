#pragma once

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

struct triangle {
	vector<point3> vertices;
	vec3 normal;

	triangle(point3 A, point3 B, point3 C) {
		vertices.push_back(A);
		vertices.push_back(B);
		vertices.push_back(C);

		// calculating the cross product for the normal
		vec3 AB = B - A;
		vec3 AC = C - A;
		normal = normalize(cross(AB, AC));
	}

	// the triangle is part of a plane if the ray pierces the plane at a location where the dot product is the same for all three sides
	// TODO: try to implement möller-trumbore
	bounceStats triangle_intersection(const ray &r) {
		// this code is adapted from möller-trumbore wikipedia page 
		vec3 AB = vertices[1] - vertices[0];
		vec3 AC = vertices[2] - vertices[0];
		vec3 direction = r.dirVec;

		vec3 r_cross_AC = cross(direction, AC);
		double eps = 1e-6;
		double det = AB.dot(r_cross_AC);
		
		if (-eps < det && det < eps) {
			return bounceStats{false, 0.0, vec3(), vec3()};
		}

		double inv_det = 1.0 / det;
		vec3 s = r.origin - vertices[0];
		double u = inv_det * s.dot(r_cross_AC);

		if (u < 0 || u > 1) return bounceStats{false, 0.0, vec3(), vec3()};

		vec3 s_cross_AB = cross(s, AB);
		double v = inv_det * direction.dot(s_cross_AB);
		if (v < 0 || u + v > 1) return bounceStats{false, 0.0, vec3(), vec3()};

		float t = inv_det * AC.dot(s_cross_AB);

		if (t > eps) {
			
			point3 intersection_point = r.loc(t);
			vec3 travelRay = t * direction;
			double rayTravelDist = travelRay.norm();
			return bounceStats{true, rayTravelDist, intersection_point, normal};
		}
		else {
			return bounceStats{false, 0.0, vec3(), vec3()};
		}
	}

};

struct sphere {
	point3 center;
	double radius;
	color3 material;
	double reflectance;
	color3 emittedColor;

	sphere(point3 c, double r, color3 m, double rf, color3 ec): center(c), radius(r), material(m), reflectance(rf), emittedColor(ec) {}

	bounceStats sphere_intersection(const ray &r) {
		// quadratic formula:
		// v = ray origin - sphere center, a = ray direction ^ 2, b = 2 * v * ray direction, c = v^2 - radius^2
		vec3 direction = r.dirVec;
		double eps = 1e-6;
		vec3 v = r.origin - center;
		double a = direction.dot(direction);
		double b = (2 * v).dot(direction);
		double c = v.dot(v) - radius * radius;
		double discriminant = b * b - 4.0 * a * c;

		if (-eps < discriminant && discriminant < eps) {
			return bounceStats{false, 0.0, vec3(), vec3()};
		}
		else {
			double t = (-b - sqrt(discriminant)) / (2.0 * a);
			vec3 travelRay = t * direction;
			double rayTravelDist = travelRay.norm();
			point3 bouncePoint = r.loc(t);
			vec3 normal = normalize(bouncePoint - center);
			if (rayTravelDist < eps) {
				return bounceStats{false, 0.0, vec3(), vec3()};
			}
			return bounceStats{true, rayTravelDist, bouncePoint, normal};
		}
		
		//return (discriminant >= epsilon);
		// we only need the discriminant since we don't care where it touches,
		// only that it does.
	}
		
};
