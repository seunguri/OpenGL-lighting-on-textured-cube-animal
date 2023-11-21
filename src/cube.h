#pragma once

#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

using namespace std;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

extern void makeCube(glm::vec4 verts[]);

class Cube {
public:
	glm::vec4 verts[NumVertices];
	glm::vec4 normals[NumVertices];

	Cube() {
		makeUV();
		computeNormals();
	};
	~Cube() {
		for (int i = 0; i < NumVertices; i++) {
			verts[i] = glm::vec4(0.0f);
			normals[i] = glm::vec4(0.0f);
		}
	}
private:
    const int NumVertices = 36;
	void makeUV();
    void quad(glm::vec4 vertices[], int a, int b, int c, int d);
	void computeNormals();
} ;
