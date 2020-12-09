#pragma once

#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include"vec.h"
#include"Matrix.h"

using namespace std;

class Shader
{
public:
	unsigned int ID;

	Shader(const GLchar* VertexPath, const GLchar* FragmentPath);
	void use();

	// uniform¹¤¾ßº¯Êý
	void setBool(const string name, bool value) const;
	void setInt(const string name, int value) const;
	void setFloat(const string name, float value) const;
	void setMat4(const std::string name, mat4 value) const;
	//void setVec3(const std::string name, glm::vec3 value) const;
	void setVec3(const string name, vec3 value) const;
	void setVec3(const string name, float value1, float value2, float value3) const;
private:
	void checkCompileErrors(unsigned int shader, string type);
};