#ifndef MESH__H_
#define MESH__H_

#include <glm\glm.hpp>
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void setVertices(glm::vec3* vertices, int vertexCount);
	void setIndices(int* indices, int indexCount);
	void useTriangleList();
	void useTriangleStrip();

	int IndexCount();
	int VertexCount();
	int TriangleCount();

	glm::vec3* const Vertices();
	int* const Indices();

protected:
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;

	int triangleCount, meshType;
};

#endif