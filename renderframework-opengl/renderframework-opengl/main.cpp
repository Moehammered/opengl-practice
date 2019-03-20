#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "HelperFunctions.h"
#include "OpenGLLoader.h"
#include "Timer.h"
#include "Mesh.h"
#include "Square.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "TransformHelperFunctions.h"
#include "Camera.h"
#include "StaticMesh.h"

///globals
//screen
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int renderSwitch = 0;

//shaders

const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;"
"layout(location = 1) in vec3 col;"
"out vec3 colour;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"  colour = col;"
"}";

const char* fragment_shader =
"#version 330 core\n"
"in vec3 colour;"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(colour, 1.0);"
"}";
///globals

void setupCubeStaticMesh(StaticMesh& mesh)
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

void setupTriangleStaticMesh(StaticMesh& mesh)
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

void setupSquareStaticMesh(StaticMesh& mesh)
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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		renderSwitch = 1;
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		renderSwitch = 0;
}

void onWindowResizeCallback(GLFWwindow* window, int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	glViewport(0, 0, width, height);
}

int main(char** argv, int argc)
{
	stbi_set_flip_vertically_on_load(true);
	OpenGLLoader* instance;
	///test glm included correctly
	glm::mat4 identity(1.0f);
	glm::mat4 world;
	glm::mat4 view;

	world = glm::translate(world, glm::vec3(0, 0, -10));
	view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	///test glm included correctly

	instance = OpenGLLoader::Instance();
	instance->setWindowSize(800, 600);

	if (!instance->initialiseOpenGL())
	{
		//error occurred...
		glfwTerminate();
		printLine("Window creation failed.");
		return -1;
	}

	instance->setWindowResizeEvent(onWindowResizeCallback);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	Shader colShader("shader.vs", "shader.fs");
	Shader textureShader("coltex-shader.vs", "coltex-shader.fs");
	Shader transformShader("transform-coltex-shader.vs", "coltex-shader.fs");

	Mesh triangle;
	
	Vertex triVertices[3];
	triVertices[0].pos = glm::vec3(-0.5f, -0.5f, 0);
	triVertices[1].pos = glm::vec3(0.5f, -0.5f, 0);
	triVertices[2].pos = glm::vec3(0, 0.5f, 0);

	triangle.setVertices(triVertices, 3);

	int indices[3];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	triangle.setIndices(indices, 3);

	std::cout << "Triangle Info" << std::endl;
	std::cout << "Vert count: " << triangle.VertexCount() << std::endl;
	std::cout << "Index count: " << triangle.IndexCount() << std::endl;
	std::cout << "Triangle count: " << triangle.TriangleCount() << std::endl;

	Mesh rectangle;
	rectangle.useTriangleStrip();

	Vertex rectangleVerts[4];
	//tri strip arrangement
	rectangleVerts[0].pos = glm::vec3(-0.5f, -0.5f, 0);
	rectangleVerts[0].colour = Colour::Blue();
	rectangleVerts[1].pos = glm::vec3(0.5f, -0.5f, 0);
	rectangleVerts[1].colour = Colour::Blue();
	rectangleVerts[2].pos = glm::vec3(-0.5f, 0.5f, 0);
	rectangleVerts[3].pos = glm::vec3(0.5f, 0.5f, 0);

	rectangle.setVertices(rectangleVerts, 4);

	int rectIndices[4];
	rectIndices[0] = 2;
	rectIndices[1] = 0;
	rectIndices[2] = 1;
	rectIndices[3] = 3;
	rectangle.setIndices(rectIndices, 4);

	std::cout << "\nRectangle Info" << std::endl;
	std::cout << "Vert count: " << rectangle.VertexCount() << std::endl;
	std::cout << "Index count: " << rectangle.IndexCount() << std::endl;
	std::cout << "Triangle count: " << rectangle.TriangleCount() << std::endl;

	
	//startup the timer
	Timer::tick();
	int clearConsolePerFrame = 10;

	Camera mainCam;
	mainCam.transform.position = glm::vec3(0, 5, 15);
	//mainCam.transform.Rotation(glm::angleAxis(glm::radians(20.0f), glm::vec3(1,0,0))); //rotation is radians!!
	mainCam.transform.rotate(glm::vec3(1, 0, 0), 20); //something weird is happening....
	mainCam.updateView();

	Square square;
	Square square2;
	StaticMesh stMesh, triStMesh, cubeSt;
	setupSquareStaticMesh(stMesh);
	setupTriangleStaticMesh(triStMesh);
	setupCubeStaticMesh(cubeSt);

	Texture containerTexture("container.jpg");
	Texture faceTexture("awesomeface.png");

	Transform sq1Tran;
	sq1Tran.position = glm::vec3(0, 0, 0);
	sq1Tran.rotate(glm::vec3(-1, 0, 0), 90);
	sq1Tran.scale = glm::vec3(10, 10, 10);

	Transform sq2Tran;
	sq2Tran.position = glm::vec3(0.5f, 0, -5);
	sq2Tran.rotate(glm::vec3(0, 0, 1), 10);
	sq2Tran.scale = glm::vec3(2, 2, 2);

	Transform cubeTran;
	glm::vec3 cubeRotAxis(1.6f, 1, 0);
	float cubeRotAngle = 1;
	cubeTran.position = glm::vec3(0, 2, 0);
	cubeTran.rotate(cubeRotAxis, cubeRotAngle);

	glm::mat4 s1World, s2World, cubeWorld;
	s1World = transformToMatrix(sq1Tran);
	s2World = transformToMatrix(sq2Tran);
	cubeWorld = transformToMatrix(cubeTran);

	unsigned int transformLoc = glGetUniformLocation(transformShader.ID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(s1World));

	glEnable(GL_CULL_FACE);

	while (!glfwWindowShouldClose(instance->getWindow()))
	{
		//calculate timing variables
		Timer::tick();
		//--clearConsolePerFrame;
		//if (clearConsolePerFrame <= 0)
		//{
		//	system("CLS"); //this is terrabad... don't use it
		//	clearConsolePerFrame = 10;
		//}
		//
		//printLine("deltaTime: " + std::to_string(Timer::DeltaTime()));
		//check input
		processInput(instance->getWindow());

		//render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glUseProgram(shader_programme);
		//bind
		//colShader.use();
		//textureShader.use();
		transformShader.use();

		//if (renderSwitch == 0)
		{
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * s1World));
			containerTexture.use();
			//draw
			//square.draw();
			stMesh.draw();
		}
		//else
		{
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * s2World));
			faceTexture.use();
			//square2.draw();
			triStMesh.draw();
		}

		
		cubeTran.rotate(cubeRotAxis, cubeRotAngle);
		cubeWorld = transformToMatrix(cubeTran);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * cubeWorld));
		containerTexture.use();
		//draw
		//square.draw();
		cubeSt.draw();

		//check for events and swap render buffers
		glfwSwapBuffers(instance->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}