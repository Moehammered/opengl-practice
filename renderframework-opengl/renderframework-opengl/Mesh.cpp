#include "Mesh.h"

#include <GLFW\glfw3.h>

Mesh::Mesh()
{
	triangleCount = 0;
	meshType = GL_TRIANGLES;
	BufferProperty bf[] = {
			{
				GL_ARRAY_BUFFER, sizeof(Vertex) * VertexCount(), Vertices(), GL_STATIC_DRAW
			},
			{
				GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * IndexCount(), Indices(), GL_STATIC_DRAW
			}
	};
	buffers.insert(buffers.begin(), bf, bf + 2);
}

Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
}

void Mesh::setVertices(const Vertex * vertices, int vertexCount)
{
	updateFlag = updateFlag | VERT_BUFFER_DATA_BIT;
	if (vertexCount > this->vertices.size())
		updateFlag = updateFlag | VERT_BUFFER_SIZE_BIT;
	this->vertices.clear();
	this->vertices.reserve(vertexCount);
	this->vertices.insert(this->vertices.begin(), vertices, vertices + vertexCount);

	updateBufferProperties();
}

void Mesh::setIndices(const int * indices, int indexCount)
{
	updateFlag = updateFlag | ELEM_BUFFER_DATA_BIT;
	if (indexCount > this->indices.size())
		updateFlag = updateFlag | ELEM_BUFFER_SIZE_BIT;
	this->indices.clear();
	this->indices.reserve(indexCount);
	this->indices.insert(this->indices.begin(), indices, indices + indexCount);

	triangleCount = meshType == GL_TRIANGLES ? indexCount / 3 : indexCount - 2;

	updateBufferProperties();
}

void Mesh::useTriangleList()
{
	meshType = GL_TRIANGLES;
	triangleCount = indices.size() / 3;
}

void Mesh::useTriangleStrip()
{
	meshType = GL_TRIANGLE_STRIP;
	triangleCount = indices.size() - 2;
}

void Mesh::forceBufferPropertyUpdate()
{
	updateFlag = updateFlag | VERT_ELEM_DATA_BITS;
	updateFlag = updateFlag | VERT_ELEM_SIZE_BITS;
	updateBufferProperties();
}

int Mesh::IndexCount()
{
	return indices.size();
}

int Mesh::VertexCount()
{
	return vertices.size();
}

int Mesh::TriangleCount()
{
	return triangleCount;
}

int Mesh::MeshType()
{
	return meshType;
}

const std::vector<BufferProperty> Mesh::VertexBufferProperty() const
{
	return buffers;
}

const Vertex * const Mesh::Vertices()
{
	return vertices.data();
}

const int * const Mesh::Indices()
{
	return indices.data();
}

void Mesh::updateBufferProperties()
{
	///flags seem unnecessary????
		///maybe move them into VAO instead as it can actually
		///perform changes to state that are costly
	if (updateFlag & 0x0)
		return; //nothing to update(no flag set)

	//if the size of the buffers needs updating (glBufferData)
	if (updateFlag & VERT_ELEM_SIZE_BITS)
	{
		if (updateFlag & VERT_BUFFER_SIZE_BIT)
		{
			//update vertexbuffer size
			buffers[0].bufferSize = VertexCount() * sizeof(Vertex);
		}
		if (updateFlag & ELEM_BUFFER_SIZE_BIT)
		{
			//update element buffer size
			buffers[1].bufferSize = IndexCount() * sizeof(unsigned int);
		}
	}

	if (updateFlag & VERT_BUFFER_DATA_BIT)
	{
		//update vert data
		buffers[0].data = Vertices();
	}
	if (updateFlag & ELEM_BUFFER_DATA_BIT)
	{
		//update elem data
		buffers[1].data = Indices();
	}

	//clear the flags
	updateFlag = 0x0;
}
