#pragma once

class vec2
{
private:
	double x, y;
public:
	vec2()
	{
		x = y = 0;
	}
	vec2(double _x, double _y) :x(_x), y(_y)
	{

	}
	vec2(double _v[2]) :x(_v[0]), y(_v[1])
	{

	}
	void set(double _x, double _y)
	{
		x = _x; y = _y;
	}
	void set(double _v[2])
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
	double x, y, z;
public:
	vec3()
	{
		x = y = z = 0;
	}
	vec3(double _x,double _y,double _z):x(_x),y(_y),z(_z)
	{

	}
	vec3(double _v[3]) :x(_v[0]), y(_v[1]), z(_v[2])
	{

	}
	void set(double _x, double _y, double _z)
	{
		x = _x; y = _y; z = _z;
	}
	void set(double _v[3])
	{
		x = _v[0]; y = _v[1]; z = _v[2];
	}
	~vec3()
	{

	}
};