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
#include "PrimitiveShapes.h"

///globals

typedef struct {
	Transform transform;
	StaticMesh mesh;
	glm::mat4 transfromMatrix;
} GameObject;

//fps demo variables
glm::vec3 pl_rot;
float pl_movespeed;
float pl_rotationspeed;
glm::vec3 pl_dir;

//screen
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int renderSwitch = 0;

void updatePlayer(GameObject& pl_go)
{
	pl_go.transfromMatrix = transformToMatrix(pl_go.transform);
}

void setupPlayer(GameObject& pl_go)
{
	PrimitiveShapes::CreateCube(pl_go.mesh);
	pl_go.transform.position = glm::vec3(-5, 1, -5);
	pl_go.transform.scale = glm::vec3(3, 3, 3);

	pl_movespeed = 5;
	pl_rotationspeed = 30;

	updatePlayer(pl_go);
}

void checkPlayerMovement(GameObject& pl_go, GLFWwindow* const window)
{
	pl_dir.x = 0;
	pl_dir.y = 0;
	pl_dir.z = 0;
	bool updatePos = false;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pl_dir += pl_go.transform.Forward();
		updatePos = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pl_dir -= pl_go.transform.Forward();
		updatePos = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		pl_dir -= pl_go.transform.Right();
		updatePos = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		pl_dir += pl_go.transform.Right();
		updatePos = true;
	}

	pl_dir.y = 0;
	if (updatePos)
	{
		pl_dir = glm::normalize(pl_dir);

		pl_go.transform.position += pl_dir * pl_movespeed * Timer::DeltaTime();
		updatePlayer(pl_go);
	}
}

void checkPlayerRotation(GameObject& pl_go, GLFWwindow* const window)
{
	pl_rot.x = 0;
	pl_rot.y = 0;
	pl_rot.z = 0;
	bool updateRotation = false;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		pl_rot.y = -1;
		updateRotation = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		pl_rot.y = 1;
		updateRotation = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		pl_rot.x = 1;
		updateRotation = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		pl_rot.x = -1;
		updateRotation = true;
	}

	if (updateRotation)
	{
		pl_go.transform.rotate(pl_rot, pl_rotationspeed * Timer::DeltaTime());
		updatePlayer(pl_go);
	}
}

void processPlayerInput(GameObject& pl_go, GLFWwindow* const window)
{
	checkPlayerRotation(pl_go, window);
	checkPlayerMovement(pl_go, window);
}

void drawPlayer(GameObject& pl_go, unsigned int transformLoc, Camera mainCam)
{
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * pl_go.transfromMatrix));
	pl_go.mesh.draw();
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


	Shader colShader("shader.vs", "shader.fs");
	Shader textureShader("coltex-shader.vs", "coltex-shader.fs");
	Shader transformShader("transform-coltex-shader.vs", "coltex-shader.fs");


	//player setup
	GameObject pl_go;
	setupPlayer(pl_go);

	//startup the timer
	Timer::tick();
	//int clearConsolePerFrame = 10;

	Camera mainCam;
	mainCam.transform.position = glm::vec3(0, 10, 15);
	mainCam.transform.lookAt(glm::vec3(0, 0, 0));
	//mainCam.transform.Rotation(glm::angleAxis(glm::radians(20.0f), glm::vec3(1,0,0))); //rotation is radians!!
	//mainCam.transform.rotate(glm::vec3(1, 0, 0), 20); //something weird is happening....
	mainCam.updateView();

	StaticMesh stMesh, triStMesh, cubeSt;
	PrimitiveShapes::CreateXYPlane(stMesh);
	PrimitiveShapes::CreateTriangle(triStMesh);
	PrimitiveShapes::CreateCube(cubeSt);

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
	glEnable(GL_DEPTH_TEST);

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
		processPlayerInput(pl_go, instance->getWindow());

		//updatePlayer(pl_go);
		//render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//bind
		//colShader.use();
		//textureShader.use();
		transformShader.use();

		//if (renderSwitch == 0)
		{
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * s1World));
			containerTexture.use();
			//draw

			stMesh.draw();
		}
		//else
		{
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * s2World));
			faceTexture.use();

			triStMesh.draw();
		}

		
		cubeTran.position = pl_go.transform.position - (pl_go.transform.Forward() * 2.0f);
		cubeTran.rotate(cubeRotAxis, cubeRotAngle);
		cubeWorld = transformToMatrix(cubeTran);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * cubeWorld));
		containerTexture.use();
		//draw

		cubeSt.draw();

		drawPlayer(pl_go, transformLoc, mainCam);

		//check for events and swap render buffers
		glfwSwapBuffers(instance->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}