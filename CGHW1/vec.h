#pragma once
#include<cmath>
#define     GLH_EPSILON          float(10e-6)
#define		GLH_EPSILON_2		float(10e-12)

class vec2
{
private:
	float x, y;
public:
	vec2()
	{
		x = y = 0;
	}
	vec2(float _x, float _y) :x(_x), y(_y)
	{

	}
	vec2(float _v[2]) :x(_v[0]), y(_v[1])
	{

	}
	void set(float _x, float _y)
	{
		x = _x; y = _y;
	}
	void set(float _v[2])
	{
		x = _v[0]; y = _v[1];
	}
	~vec2()
	{

	}
};

class vec3
{
private:
	float x, y, z;
public:
	vec3()
	{
		x = y = z = 0;
	}
	vec3(float _x,float _y,float _z):x(_x),y(_y),z(_z)
	{

	}
	vec3(float _v[3]) :x(_v[0]), y(_v[1]), z(_v[2])
	{

	}
	void set(float _x, float _y, float _z)
	{
		x = _x; y = _y; z = _z;
	}
	void set(float _v[3])
	{
		x = _v[0]; y = _v[1]; z = _v[2];
	}
	~vec3()
	{

	}
	float getx() const
	{
		return x;
	}
	float gety() const
	{
		return y;
	}
	float getz() const
	{
		return z;
	}
	vec3& operator += (const vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3& operator -= (const vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3 operator - () const {
		return vec3(-x, -y, -z);
	}
	vec3 operator+ (const vec3& v) const
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	float dot(const vec3& vec) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}
	vec3 cross(const vec3& vec) const
	{
		return vec3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
	}

	vec3& operator *= (float t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}
	vec3 operator *(float t) const
	{
		return vec3(x * t, y * t, z * t);
	}

	float length() const {
		return float(sqrt(x * x + y * y + z * z));
	}

	void normalize()
	{
		float sum = x * x + y * y + z * z;
		if (sum > GLH_EPSILON_2) {
			float base = float(1.0 / sqrt(sum));
			x *= base;
			y *= base;
			z *= base;
		}
	}
};

inline vec3 operator * (float t, const vec3& v) {
	return v * t;
}

inline float operator * (const vec3& v1, const vec3& v2) {
	return v1.dot(v2);
}

inline vec3 normalize(const vec3& vec)
{
	vec3 nvec=vec;
	nvec.normalize();
	return nvec;
}

inline vec3 cross(const vec3& vec1, const vec3& vec2)
{
	return vec1.cross(vec2);
}