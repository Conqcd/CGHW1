#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include"mesh.h"
using namespace std;

void readObj(const char* filename,mesh* &object);

int main()
{
	mesh* object=nullptr;
	string filename = "example.obj";
	readObj(filename.c_str(),object);

	delete object;
	return 0;
}

void readObj(const char* filename, mesh* &object)
{
	if (object != nullptr)
	{
		delete object;
	}
	fstream file;
	file.open(filename);
	if (!file.is_open())
	{
		printf("Can not read file:%s\n", filename);
		return;
	}
	string line;
	unsigned int numbVtx,numTri,numTex,numNor, numbVtx2, numTri2, numTex2, numNor2;
	numbVtx = numTri = numTex = numNor = numbVtx2 = numTri2 = numTex2 = numNor2 = 0;
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
			nface[numTri2].setv(id1, id2, id3);
			nface[numTri2].sett(id4, id5, id6);
			nface[numTri2++].setn(id7, id8, id9);
		}
	}
	object = new mesh(numbVtx2, numTri2, nface, nvertex, nnormal, ntexcord);
}