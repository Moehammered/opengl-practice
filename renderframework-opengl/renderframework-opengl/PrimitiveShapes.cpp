#include "PrimitiveShapes.h"

namespace PrimitiveShapes
{
	void CreateCube(StaticMesh& mesh)
	{
		mesh.useTriangleList();
		Vertex vertices[8];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0.5f); //FTL
		//vertices[0].colour = Colour::Blue();
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0.5f); //FBL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0.5f, 0.5f); //FTR
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, -0.5f, 0.5f); //FBR
		vertices[3].uv = glm::vec2(1, 0);

		vertices[4].pos = glm::vec3(0.5f, 0.5f, -0.5f); //BTR
		//vertices[0].colour = Colour::Blue();
		vertices[4].uv = glm::vec2(0, 1);
		vertices[5].pos = glm::vec3(0.5f, -0.5f, -0.5f); //BBR
		vertices[5].uv = glm::vec2(0, 0);
		vertices[6].pos = glm::vec3(-0.5f, 0.5f, -0.5f); //BTL
		vertices[6].uv = glm::vec2(1, 1);
		vertices[7].pos = glm::vec3(-0.5f, -0.5f, -0.5f); //BBL
		vertices[7].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[36]{
			0, 1, 2,	//1st tri //front face
			2, 1, 3,	//2nd tri

			4, 2, 3,	//1st tri //right face
			4, 3, 5,	//2nd tri

			4, 5, 6,	//1st tri //back face
			5, 7, 6,	//2nd tri

			0, 6, 7,	//1st tri //left face
			0, 7, 1,	//2nd tri

			6, 0, 2,	//1st tri //top face
			6, 2, 4,	//2nd tri

			3, 1, 7,	//1st tri //bottom face
			3, 7, 5		//2nd tri
		};

		mesh.setVertices(vertices, 8);
		mesh.setIndices(indices, 36);
		mesh.updateMesh();
	}

	void CreateXYPlane(StaticMesh& mesh)
	{
		mesh.useTriangleList();
		Vertex vertices[4];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0); //TL
		//vertices[0].colour = Colour::Blue();
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0); //BL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0.5f, 0); //TR
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, -0.5f, 0); //BR
		vertices[3].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[6]{
			0, 1, 2,	//1st tri
			2, 1, 3		//2nd tri
		};

		mesh.setVertices(vertices, 4);
		mesh.setIndices(indices, 6);
		mesh.updateMesh();
	}

	void CreateXZPlane(StaticMesh& mesh)
	{
		mesh.useTriangleList();
		Vertex vertices[4];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0, -0.5f); //TL
		//vertices[0].colour = Colour::Blue();
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, 0, 0.5f); //BL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0, -0.5f); //TR
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, 0, 0.5f); //BR
		vertices[3].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[6]{
			0, 1, 2,	//1st tri
			2, 1, 3		//2nd tri
		};

		mesh.setVertices(vertices, 4);
		mesh.setIndices(indices, 6);
		mesh.updateMesh();
	}

	void CreateTriangle(StaticMesh& mesh)
	{
		mesh.useTriangleList();
		Vertex vertices[3];
		//setup the positions
		vertices[0].pos = glm::vec3(0, 0.5f, 0); //TM
		//vertices[0].colour = Colour::Blue();
		vertices[0].uv = glm::vec2(0.5f, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0); //BL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, -0.5f, 0); //BR
		vertices[2].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[3]{
			0, 1, 2	//1st tri
		};

		mesh.setVertices(vertices, 3);
		mesh.setIndices(indices, 3);
		mesh.updateMesh();
	}

}