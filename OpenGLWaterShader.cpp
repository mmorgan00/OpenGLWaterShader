// OpenGLWaterShader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <GL\glew.h>
#include <GL\freeglut.h>

void setupWindow()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// Set the window size
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Water Renderer");
	GLenum res = glewInit();

	// ensure it was started properly
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 0;
	}
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	setupWindow();
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
