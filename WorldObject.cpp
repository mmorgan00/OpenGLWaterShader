#include "WorldObject.h"
using namespace lodepng;


WorldObject::WorldObject(char* meshFileName,
	char* texFileName,
	char* normMapFileName,
	char* dispMapFileName)
{

	meshFile = meshFileName;
	// init VAO
	cyTriMesh mesh = cyTriMesh();
	mesh.LoadFromFileObj(meshFile);
	mesh.ComputeNormals();
	mesh.ComputeBoundingBox();
	for (unsigned int i = 0; i < mesh.NF(); i++)
	{
		cy::TriMesh::TriFace face = mesh.F(i);
		cy::TriMesh::TriFace textureFace = mesh.FT(i);
		for (int j = 0; j < 3; j++)
		{
			int vertIndex = face.v[j];
			int texIndex = textureFace.v[j];
			cy::Vec3f normal;
			normal = mesh.VN(vertIndex);
			// FT
			cy::Vec3f vert = mesh.V(vertIndex);
			vertices.push_back(cyVec3f(vert.x, vert.y, vert.z));
			normals.push_back(cyVec3f(normal.x, normal.y, normal.z));
			cyVec3f texCoord = mesh.VT(texIndex);
			texCoords.push_back(cyVec2f(texCoord.x, texCoord.y)); // face index for the current vertex
		}
	}

	// Initialize VBOs and VAO

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &vertVBO);
	glGenBuffers(1, &normVBO);
	glGenBuffers(1, &texVBO);

	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(cy::Vec3f), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normVBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(cyVec3f), &normals[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(cyVec2f), &texCoords[0], GL_STATIC_DRAW);


	if (texFileName)
	{
		textureFile = texFileName;

		// parse and generate texture data
		vector<unsigned char> textureBuffer;
		unsigned width, height;
		decode(textureBuffer, width, height, texFileName);
		textureMap.Initialize();
		textureMap.SetImage(&textureBuffer[0], 4, width, height);
	}

	if (normMapFileName)
	{
		normalMapFile = normMapFileName;

		// parse and generate texture data
		vector<unsigned char> normalMapBuffer;
		unsigned width, height;
		decode(normalMapBuffer, width, height, normMapFileName);
		normalMap.Initialize();
		normalMap.SetImage(&normalMapBuffer[0], 4, width, height);
	}

	if (displacementMapFile)
	{
		displacementMapFile = dispMapFileName;
		vector<unsigned char> displaceMapBuffer;
		unsigned width, height;
		decode(displaceMapBuffer, width, height, displacementMapFile);
		displacementMap.Initialize();
		displacementMap.SetImage(&displaceMapBuffer[0], 4, width, height);
	}
}