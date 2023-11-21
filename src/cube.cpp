#include "cube.h"


void Cube::makeUV()
{
	// make vertex list
	glm::vec4 vertices[8] = {
		glm::vec4(-0.5, -0.5, 0.5, 1.0),
		glm::vec4(-0.5, 0.5, 0.5, 1.0),
		glm::vec4(0.5, 0.5, 0.5, 1.0),
		glm::vec4(0.5, -0.5, 0.5, 1.0),
		glm::vec4(-0.5, -0.5, -0.5, 1.0),
		glm::vec4(-0.5, 0.5, -0.5, 1.0),
		glm::vec4(0.5, 0.5, -0.5, 1.0),
		glm::vec4(0.5, -0.5, -0.5, 1.0)
		};

	glm::vec2 texcoord[4] = {
		glm::vec2(-0.5, 0.5),
		glm::vec2(-0.5, -0.5),
		glm::vec2(0.5, -0.5),
		glm::vec2(0.5, 0.5)
	};


	// make triangles and textures
	quad(vertices, texcoord, 1, 0, 3, 2);
	quad(vertices, texcoord, 2, 3, 7, 6);
	quad(vertices, texcoord, 3, 0, 4, 7);
	quad(vertices, texcoord, 6, 5, 1, 2);
	quad(vertices, texcoord, 4, 5, 6, 7);
	quad(vertices, texcoord, 5, 4, 0, 1);
};

int Index = 0;
void Cube::quad(glm::vec4 vertices[], glm::vec2 texcoord[], int a, int b, int c, int d)
{
	verts[Index] = vertices[a];  texCoords[Index] = texcoord[0];	Index++;
	verts[Index] = vertices[b];  texCoords[Index] = texcoord[1];	Index++;
	verts[Index] = vertices[c];  texCoords[Index] = texcoord[2];	Index++;
	verts[Index] = vertices[a];  texCoords[Index] = texcoord[0];	Index++;
	verts[Index] = vertices[c];  texCoords[Index] = texcoord[2];	Index++;
	verts[Index] = vertices[d];  texCoords[Index] = texcoord[3];	Index++;
}

void Cube::computeNormals()
{
	for (int i = 0; i < NumVertices; i++)
	{
		glm::vec4 n;
		for (int k = 0; k < 3; k++)
		{
			n[k] = verts[i][k];
		}
		n[3] = 0.0;
		glm::normalize(n);
		normals[i] = n;
	}
}
