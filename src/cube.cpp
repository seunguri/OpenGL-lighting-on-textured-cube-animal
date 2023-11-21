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


	// make triangles and textures
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
	glm::vec2 texcoord[4];
	computeTexCoordQuad(texcoord, a, b, c, d);

	verts[Index] = vertices[a];  texCoords[Index] = texcoord[a];	Index++;
	verts[Index] = vertices[b];  texCoords[Index] = texcoord[b];	Index++;
	verts[Index] = vertices[c];  texCoords[Index] = texcoord[c];	Index++;
	verts[Index] = vertices[a];  texCoords[Index] = texcoord[a];	Index++;
	verts[Index] = vertices[c];  texCoords[Index] = texcoord[c];	Index++;
	verts[Index] = vertices[d];  texCoords[Index] = texcoord[d];	Index++;
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

void Cube::computeTexCoordQuad(glm::vec2 texcoord[4], int a, int b, int c, int d)
{
	const int U = 0, V = 1;
	// v0=(u, v)    v1=(u2, v)   <= quadangle
	// v2=(u, v2)   v3=(u2, v2)

	texcoord[0][U] = texcoord[2][U] = (float)a / NumVertices;
	texcoord[1][U] = texcoord[3][U] = (float)b / NumVertices;

	texcoord[0][V] = texcoord[1][V] = (float)c / NumVertices;
	texcoord[2][V] = texcoord[3][V] = (float)d / NumVertices;

	if (b == 0) // last column
	{
		texcoord[1][U] = texcoord[3][U] = 1.0;
	}
}
