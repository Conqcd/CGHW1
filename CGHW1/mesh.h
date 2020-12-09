#pragma once

#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include"tri.h"
#include"Shader.h"

class mesh
{
private:
	unsigned int numvtx, numtri,numind;
	tri* face;
	vec3* vertex;
	vec3* normal;
	vec2* texcord;
	unsigned int VAO, VBO, EBO;
	unsigned int* indices;
public:
	mesh();
	mesh(unsigned int _numvtx, unsigned int _numtri, unsigned int _numind,
	tri* _face,
	vec3* _vertex,
	vec3* _normal,
	vec2* _texcord,
	unsigned int* _indices);
	~mesh();
	void draw(Shader* shader);
	void SetUpShader();
};