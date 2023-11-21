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

	// make triangles
	quad(vertices, 1, 0, 3, 2);
	quad(vertices, 2, 3, 7, 6);
	quad(vertices, 3, 0, 4, 7);
	quad(vertices, 6, 5, 1, 2);
	quad(vertices, 4, 5, 6, 7);
	quad(vertices, 5, 4, 0, 1);
};

int Index = 0;
void Cube::quad(glm::vec4 vertices[], int a, int b, int c, int d)
{
	verts[Index] = vertices[a];  Index++;
	verts[Index] = vertices[b];  Index++;
	verts[Index] = vertices[c];  Index++;
	verts[Index] = vertices[a];  Index++;
	verts[Index] = vertices[c];  Index++;
	verts[Index] = vertices[d];  Index++;
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
