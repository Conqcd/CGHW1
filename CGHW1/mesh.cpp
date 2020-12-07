#include "mesh.h"

mesh::mesh()
{

}

mesh::mesh(unsigned int _numvtx, unsigned int _numtri,
	tri* _face,
	vec3* _vertex,
	vec3* _normal,
	vec2* _texcord)
{
	numvtx = _numvtx;
	numtri = _numtri;
	face = _face;
	vertex = _vertex;
	normal = _normal;
	texcord = _texcord;
}

mesh::~mesh()
{
	delete[] face;
	delete[] vertex;
	delete[] normal;
	delete[] texcord;
}