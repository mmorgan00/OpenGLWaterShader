// OpenGLWaterShader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Renderer.h"
#include "cyGL/cyGL.h"
#include "cyGL/cyMatrix.h"


vector<cyVec3f> gridVerts;
GLuint heightGridVAO;
GLuint heightGridVertVBO;
cyGLSLProgram heightGridProgram;
Camera camera;

void createHeightGrid()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			gridVerts.push_back(cyVec3f(-0.5f + (0.1 * i), -0.5f + (0.1 * j), 0));
		}
	}

	glGenVertexArrays(1, &heightGridVAO);
	glBindVertexArray(heightGridVAO);

	glGenBuffers(1, &heightGridVertVBO);
	glBindBuffer(GL_ARRAY_BUFFER, heightGridVertVBO);
	glBufferData(GL_ARRAY_BUFFER, gridVerts.size() * sizeof(cy::Vec3f), &gridVerts[0], GL_STATIC_DRAW);
	
	glVertexArrayVertexBuffer(heightGridVAO, 0, heightGridVertVBO, 0, sizeof(cyVec3f));
	glVertexArrayAttribBinding(heightGridVAO, 0, 0);
	glVertexArrayAttribFormat(heightGridVAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(cyVec3f, x));
	glVertexArrayBindingDivisor(heightGridVAO, 0, 0);


	glEnableVertexArrayAttrib(heightGridVAO, 0);
	
	boolean success = heightGridProgram.BuildFiles("shader.vert", "shader.frag");
	if (!success) {
		std::cout << "Error building shaders" << std::endl;
	}
	GLint viewloc = glGetUniformLocation(heightGridProgram.GetID(), "view");
	glUniformMatrix4fv(viewloc, 1, GL_TRUE, &camera.view[0]);
	glEnableVertexAttribArray(0);

}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(heightGridVAO);
	heightGridProgram.Bind(); // equivalent ot the glUseProgram() call
	glDrawArrays(GL_POINTS, 0, gridVerts.size());
	glutSwapBuffers();
}

void setupWindow()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Water Renderer");
	glutDisplayFunc(render);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// Set the window size
	GLenum res = glewInit();

	// ensure it was started properly
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}
}



int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	setupWindow();
	camera = Camera();
	createHeightGrid();
	
	
	glutMainLoop();
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
