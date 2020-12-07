#pragma once
#include"tri.h"
class mesh
{
public:
	unsigned int numvtx, numtri;
	tri* face;
	vec3* vertex;
	vec3* normal;
	vec2* texcord;
public:
	mesh();
	mesh(unsigned int _numvtx, unsigned int _numtri,
	tri* _face,
	vec3* _vertex,
	vec3* _normal,
	vec2* _texcord);
	~mesh();
};