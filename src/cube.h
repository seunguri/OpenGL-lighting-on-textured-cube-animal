#pragma once

#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

using namespace std;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

extern void makeCube(vector<glm::vec4> *verts);

class Cube {
public:
	vector<glm::vec4> verts;
	vector<glm::vec4> normals;

	Cube() {
		makeUV();
		computeNormals();
	};
	~Cube() {
		verts.clear();
		vector<glm::vec4>().swap(verts);
		normals.clear();
		vector<glm::vec4>().swap(normals);
	}
private:
    const int NumVertices = 36;
	void makeUV();
	void computeNormals();
} ;
