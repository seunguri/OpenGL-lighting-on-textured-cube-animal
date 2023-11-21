#include "initShader.h"
#include "cube.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

enum eShadeMode { NO_LIGHT, GOURAUD, PHONG, NUM_LIGHT_MODE };

glm::mat4 projectMat;
glm::mat4 viewMat;
glm::mat4 modelMat = glm::mat4(1.0f);

int shadeMode = NO_LIGHT;
int isRotate = false;
float upperLegAngle = 0.0f;
float lowerLegAngle = 0.0f;

GLuint projectMatrixID;
GLuint viewMatrixID;
GLuint modelMatrixID;
GLuint shadeModeID;

Cube cube {};


// OpenGL initialization
void init()
{
	// Create a vertex array object
	GLuint vao[1];
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	// Create and initialize a buffer object
	GLuint buffer[1];
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);

	int vertSize = sizeof(cube.verts[0])*cube.verts.size();
	int normalSize = sizeof(cube.normals[0])*cube.normals.size();
	glBufferData(GL_ARRAY_BUFFER, vertSize + normalSize,
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertSize, cube.verts.data());
	glBufferSubData(GL_ARRAY_BUFFER, vertSize, normalSize, cube.normals.data());

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("src/vshader.glsl", "src/fshader.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(vertSize));

	projectMatrixID = glGetUniformLocation(program, "mProject");
	projectMat = glm::perspective(glm::radians(65.0f), 1.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(projectMatrixID, 1, GL_FALSE, &projectMat[0][0]);

	viewMatrixID = glGetUniformLocation(program, "mView");
	viewMat = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMat[0][0]);

	modelMatrixID = glGetUniformLocation(program, "mModel");
	modelMat = glm::mat4(1.0f);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMat[0][0]);

	shadeModeID = glGetUniformLocation(program, "shadeMode");
	glUniform1i(shadeModeID, shadeMode);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

//----------------------------------------------------------------------------

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMat[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, cube.verts.size());

// 	worldMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));
// 	drawHorse(worldMat);

	glutSwapBuffers();
}

//----------------------------------------------------------------------------

void idle()
{
	static int prevTime = glutGet(GLUT_ELAPSED_TIME);
	int currTime = glutGet(GLUT_ELAPSED_TIME);

	if (isRotate && abs(currTime - prevTime) >= 20)
	{
		float t = abs(currTime - prevTime);
		float speed = 360.0f / 100000.0f;
		modelMat = glm::rotate(modelMat, glm::radians(t*speed), glm::vec3(1.0f, 1.0f, 0.0f));
        // upperLegAngle = glm::radians(30.0f) * sin(glm::radians(currTime * 360.0f / 1000.0f));
		// lowerLegAngle = glm::radians(30.0f) * sin(glm::radians(currTime * 360.0f / 990.0f));
		prevTime = currTime;
		glutPostRedisplay();
	}
}

//----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'l': case 'L':
		shadeMode = (++shadeMode % NUM_LIGHT_MODE);
		glUniform1i(shadeModeID, shadeMode);
		glutPostRedisplay();
		break;
	case 'r': case 'R':
		isRotate = !isRotate;
		glutPostRedisplay();
		break;
	case 033:  // Escape key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}
}

//----------------------------------------------------------------------------

void resize(int w, int h)
{
	float ratio = (float)w / (float)h;
	glViewport(0, 0, w, h);

	projectMat = glm::perspective(glm::radians(65.0f), ratio, 0.1f, 100.0f);
	glUniformMatrix4fv(projectMatrixID, 1, GL_FALSE, &projectMat[0][0]);
	glutPostRedisplay();
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Horse");

	glewInit();

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


// void drawHorse(glm::mat4 horseMat)
// {
// 	glm::mat4 modelMat, pvmMat;
// 	glm::vec3 legPos[4];
// 	glm::vec3 lowerlegPos = glm::vec3(0, -0.5, 0);
// 	glm::vec3 earPos[2];

// 	legPos[0] = glm::vec3(0.4, -0.4, -0.1); // rear right uppper
// 	legPos[1] = glm::vec3(0.4, -0.4, 0.1); // rear left uppper
// 	legPos[2] = glm::vec3(-0.4, -0.4, -0.1); // front right uppper
// 	legPos[3] = glm::vec3(-0.4, -0.4, 0.1); // front left uppper

// 	earPos[1] = glm::vec3(-0.8, 0.5, -0.1); // right
// 	earPos[0] = glm::vec3(-0.8, 0.5, 0.1); // left

// 	// horse body
// 	modelMat = glm::scale(horseMat, glm::vec3(1, 0.5, 0.4));
// 	pvmMat = projectMat * viewMat * modelMat;
// 	glUniformMatrix4fv(pvmMatrixID, 1, GL_FALSE, &pvmMat[0][0]);
// 	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

// 	// horse neck
// 	modelMat = glm::translate(horseMat, glm::vec3(-0.6, 0.3, 0));
// 	modelMat = glm::rotate(modelMat, glm::radians(45.0f), glm::vec3(0, 0, 1.0f));
// 	modelMat = glm::scale(modelMat, glm::vec3(0.3, 0.5, 0.3));
// 	pvmMat = projectMat * viewMat * modelMat;
// 	glUniformMatrix4fv(pvmMatrixID, 1, GL_FALSE, &pvmMat[0][0]);
// 	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

// 	// horse head
// 	modelMat = glm::translate(horseMat, glm::vec3(-0.77, 0.3, 0));
// 	modelMat = glm::rotate(modelMat, glm::radians(-45.0f), glm::vec3(0, 0, 1.0f));
// 	modelMat = glm::scale(modelMat, glm::vec3(0.25, 0.45, 0.29));
// 	pvmMat = projectMat * viewMat * modelMat;
// 	glUniformMatrix4fv(pvmMatrixID, 1, GL_FALSE, &pvmMat[0][0]);
// 	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

// 	// horse ear
// 	for (int i = 0; i < 2; i++)
// 	{
// 		modelMat = glm::translate(horseMat, earPos[i]);
// 		modelMat = glm::scale(modelMat, glm::vec3(0.05, 0.2, 0.05));
// 		//modelMat = glm::rotate(modelMat, glm::radians(15.0f), glm::vec3(1.0f, 0, 0));
// 		pvmMat = projectMat * viewMat * modelMat;
// 		glUniformMatrix4fv(pvmMatrixID, 1, GL_FALSE, &pvmMat[0][0]);
// 		glDrawArrays(GL_TRIANGLES, 0, NumVertices);
// 	}

// 	// horse tail
// 	modelMat = glm::translate(horseMat, glm::vec3(0.6, 0, 0));  //P*V*C*T*S*v
// 	modelMat = glm::rotate(modelMat, glm::radians(30.0f), glm::vec3(0, 0, 1.0f));
// 	modelMat = glm::scale(modelMat, glm::vec3(0.1, 0.5, 0.1));
// 	pvmMat = projectMat * viewMat * modelMat;
// 	glUniformMatrix4fv(pvmMatrixID, 1, GL_FALSE, &pvmMat[0][0]);
// 	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

// 	// horse leg
// 	for (int i = 0; i < 4; i++)
// 	{
// 		float dir = 1.0f;
// 		if (i % 2 != 0)
// 			dir = -1.0f;
// 		// upper
// 		modelMat = glm::translate(horseMat, legPos[i] + glm::vec3(0, 0.2, 0));
// 		modelMat = glm::rotate(modelMat, dir * upperLegAngle, glm::vec3(0, 0, 1));
// 		modelMat = glm::translate(modelMat, glm::vec3(0, -0.2, 0));
// 		modelMat = glm::scale(modelMat, glm::vec3(0.15, 0.35, 0.15));
// 		pvmMat = projectMat * viewMat * modelMat;
// 		glUniformMatrix4fv(pvmMatrixID, 1, GL_FALSE, &pvmMat[0][0]);
// 		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

// 		// lower
// 		modelMat = glm::translate(horseMat, legPos[i] + glm::vec3(0, 0.2, 0));
// 		modelMat = glm::rotate(modelMat, dir * upperLegAngle, glm::vec3(0, 0, 1));
// 		modelMat = glm::translate(modelMat, lowerlegPos + glm::vec3(0, 0.05, 0));
// 		modelMat = glm::rotate(modelMat, -dir * lowerLegAngle, glm::vec3(0, 0, 1));
// 		modelMat = glm::translate(modelMat, glm::vec3(0, -0.05, 0));
// 		modelMat = glm::scale(modelMat, glm::vec3(0.15, 0.25, 0.15));

// 		pvmMat = projectMat * viewMat * modelMat;
// 		glUniformMatrix4fv(pvmMatrixID, 1, GL_FALSE, &pvmMat[0][0]);
// 		glDrawArrays(GL_TRIANGLES, 0, NumVertices);
// 	}
// }