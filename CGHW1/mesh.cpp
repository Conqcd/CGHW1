#include "mesh.h"

mesh::mesh()
{

}

mesh::mesh(unsigned int _numvtx, unsigned int _numtri, unsigned int _numind,
	tri* _face,
	vec3* _vertex,
	vec3* _normal,
	vec2* _texcord,
	unsigned int* _indices)
{
	numvtx = _numvtx;
	numind = _numind;
	numtri = _numtri;
	face = _face;
	vertex = _vertex;
	normal = _normal;
	texcord = _texcord;
	indices = _indices;
	SetUpShader();
}

mesh::~mesh()
{
	delete[] face;
	delete[] vertex;
	delete[] normal;
	delete[] texcord;
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &EBO);
	glDeleteBuffers(1, &VBO);
}


void mesh::draw(Shader* shader)
{

	unsigned int specularNr = 1;
	unsigned int diffuseNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	/*for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); 
		string name = textures[i].type;
		string number;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); 
		else if (name == "texture_normal")
			number = std::to_string(normalNr++);
		else if (name == "texture_height")
			number = std::to_string(heightNr++);

		glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}*/

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numind, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void mesh::SetUpShader()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(VBO, sizeof(vec3) * numvtx, &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numind, &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);

	/*glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));*/

	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
	glBindVertexArray(0);
}
