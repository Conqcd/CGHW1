#pragma once

#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include"Shader.h"
#include<vector>
#include"mesh.h"
using namespace std;

class Model
{
public:
	Model(const char* path, bool gamma);
	void Draw(Shader* shader);

public:
	vector<shared_ptr<mesh>> meshes;
	string directory;
	//vector<Texture> load_textures;
	bool gammaCorrection;

private:
	void loadModel(string path, shared_ptr<mesh>& object);
	/*void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);*/
};