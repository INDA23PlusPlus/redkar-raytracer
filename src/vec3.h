#pragma once

#include <cmath>
#include <iostream>
#include <random> 

using namespace std;

class vec3 {
public:
	double x, y, z;
	vec3() {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	vec3(double x, double y, double z): x(x), y(y), z(z) {}

	void operator +=(const vec3 &v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	void operator *=(double t) {
		x *= t;
		y *= t;
		z *= t;
	}
	void operator /=(double t) {
		x /= t;
		y /= t;
		z /= t;
	}
	double norm_squared() const {
		return x*x + y*y + z*z;
	}

	double norm() const {
		return sqrt(norm_squared());
	}

	double dot(const vec3 &v) {
		return x*v.x + y*v.y + z*v.z;
	}
};

using point3 = vec3;
using color3 = vec3;

inline vec3 operator +(const vec3 &u, const vec3 &v) {
	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}
inline vec3 operator -(const vec3 &u, const vec3 &v) {
	return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}
inline vec3 operator *(const vec3 &u, const vec3 &v) {
	return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}
inline vec3 operator *(double t, const vec3 &v) {
	return vec3(t*v.x, t*v.y, t*v.z);
}
inline vec3 operator *(const vec3 &v, double t) {
	return t * v;
}
inline vec3 operator /(const vec3 &v, double t) {
	return (1/t) * v;
}
inline vec3 normalize(vec3 v) {
	return v / v.norm();
}
inline vec3 cross(const vec3 &u, const vec3 &v) {
	return vec3(u.y * v.z - u.z * v.y,
		    u.z * v.x - u.x * v.z,
		    u.x * v.y - u.y * v.x);
}

inline double random_double() { // putting this here, since vec3.h is included everywhere
    static uniform_real_distribution<double> distribution(0.0, 1.0);
    static mt19937 generator;
    return distribution(generator);
}

vec3 random_vector() {
	vec3 rand_vec(random_double(), random_double(), random_double());
	normalize(rand_vec);
	return rand_vec;
}
