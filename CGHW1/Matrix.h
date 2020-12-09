#pragma once
#include"vec.h"
#include <algorithm>
using namespace std;

class mat4
{
public:
	float _data[4][4];
public:
	mat4()
	{
		zero();
	}
	mat4(float num)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					_data[i][j] = num;
				else
					_data[i][j] = 0;
			}
		}
	}
	~mat4()
	{

	}
	void zero()
	{
		memset(&_data[0][0], 0, sizeof(float) * 16);
	}

	float* operator[] (int x) 
	{
		return _data[x];
	}
	const float* operator[] (int x) const
	{
		return _data[x];
	}
	mat4 operator*(const mat4& rhs)  {
		mat4 result;
		for (int r = 0; r < 4; ++r) {
			for (int c = 0; c < 4; ++c) {
				float val = 0;
				for (int i = 0; i < 4; ++i) {
					val += operator[](r)[i] * rhs[i][c];
				}
				result[r][c] = val;
			}
		}
		return result;
	}
};

inline mat4 perspective(float a, float b,float c, float d)
{
	return mat4(1.0f);
}

inline mat4 translate(const mat4& m,const vec3& vec)
{
	mat4 m2 = m;
	m2[0][3] = vec.getx();
	m2[1][3] = vec.gety();
	m2[2][3] = vec.getz();
	return m2;
}

inline mat4 scale(const mat4& m, const vec3& vec)
{
	mat4 m2 = m;
	m2[0][0] *= vec.getx();
	m2[1][1] *= vec.gety();
	m2[2][2] *= vec.getz();
	return m2;
}