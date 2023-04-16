#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include "cyGL/cyGL.h"
#include "cyGL/cyTriMesh.h"
#include "cyGL/cyMatrix.h"
#include "lodepng.h"

using namespace std;

class WorldObject
{
	// VAO information
	GLuint VAO;
	GLuint vertVBO;
	GLuint normVBO;
	GLuint texVBO;

	// texture samplers needed for rendering
	cyGLTexture2D textureMap;
	cyGLTexture2D normalMap;
	cyGLTexture2D displacementMap;



	// represented as file paths, will be decoded at runtime
	char* textureFile = nullptr;
	char* normalMapFile = nullptr;
	char* displacementMapFile = nullptr;
	char* meshFile;

private:

	// holds data internally, OpenGL calls need as a VBO 
	vector<cyVec3f> vertices;
	vector<cyVec3f> normals;
	vector<cyVec2f> texCoords;

	WorldObject(char* meshFileName,
		char* texFileName = nullptr,
		char* normMapFileName = nullptr,
		char* dispMapFileName = nullptr);
	


};

