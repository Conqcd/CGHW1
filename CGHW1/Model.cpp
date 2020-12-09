#include "Model.h"

Model::Model(const char* path, bool gamma = false) :gammaCorrection(gamma)
{
	shared_ptr<mesh> object;
	loadModel(path, object);
	meshes.push_back(object);
}

void Model::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->draw(shader);
	}
}

void Model::loadModel(string filename, shared_ptr<mesh>& object)
{
	int i = 0;
	/*if (object != nullptr)
	{
		delete object;
	}*/
	fstream file;
	file.open(filename);
	if (!file.is_open())
	{
		printf("Can not read file:%s\n", filename);
		return;
	}
	string line;
	unsigned int numbVtx, numTri, numTex, numNor, numbVtx2, numTri2, numTex2, numNor2, numbInd;
	numbVtx = numTri = numTex = numNor = numbVtx2 = numTri2 = numTex2 = numNor2 = numbInd = 0;
	while (getline(file, line))
	{
		if (line[0] == 'v')
		{
			if (line[1] == ' ')
			{
				numbVtx++;
			}
			else if (line[1] == 't')
			{
				numTex++;
			}
			else if (line[1] == 'n')
			{
				numNor++;
			}
		}
		else if (line[0] == 'f')
		{
			numTri++;
		}
	}
	file.close();
	file.open(filename);
	tri* nface = new tri[numTri];
	vec3* nvertex = new vec3[numbVtx];
	vec3* nnormal = new vec3[numNor];
	vec2* ntexcord = new vec2[numTex];
	unsigned int* indices = new unsigned int[numTri*3];
	while (getline(file, line))
	{
		if (line[0] == 'v')
		{
			const char* st = line.c_str();
			if (line[1] == ' ')
			{
				double x, y, z;
				sscanf(st+2, "%lf%lf%lf", &x, &y, &z);
				nvertex[numbVtx2++].set(x, y, z);
			}
			else if (line[1] == 't')
			{
				double x, y;
				sscanf(st+2, "%lf%lf", &x, &y);
				ntexcord[numTex2++].set(x, y);
			}
			else if (line[1] == 'n')
			{
				double x, y, z;
				sscanf(st+2, "%lf%lf%lf", &x, &y, &z);
				nnormal[numNor2++].set(x, y, z);
			}
		}
		else if (line[0] == 'f'&& line[1] == ' ')
		{
			const char* st = line.c_str();
			unsigned id1, id2, id3, id4, id5, id6, id7, id8, id9;
			sscanf(st+2, "%u/%u/%u %u/%u/%u %u/%u/%u", &id1, &id2, &id3, &id4, &id5, &id6, &id7, &id8, &id9);
			indices[numbInd++] = id1-1;
			indices[numbInd++] = id2-1;
			indices[numbInd++] = id3-1;
			nface[numTri2].setv(id1, id2, id3);
			nface[numTri2].sett(id4, id5, id6);
			nface[numTri2++].setn(id7, id8, id9);
		}
	}
	object = make_shared<mesh>(numbVtx2, numTri2, numbInd, nface, nvertex, nnormal, ntexcord, indices);
}