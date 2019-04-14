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
#include "Line.h"
#include "GameObject.h"
#include "FPSDemo.h"
#include "Input.h"
///globals

//fps demo variables
glm::vec3 pl_rot;
float pl_movespeed;
float pl_rotationspeed;
glm::vec3 pl_dir;

//screen
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int renderSwitch = 0;

void setupPlayer(GameObject& pl_go, StaticMesh& pl_sm)
{
	PrimitiveShapes::CreateCube(pl_sm);
	pl_go.transform.position = glm::vec3(-5, 1, -5);
	pl_go.transform.scale = glm::vec3(3, 3, 3);

	pl_movespeed = 5;
	pl_rotationspeed = 30;
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

	//pl_dir.y = 0;
	if (updatePos)
	{
		pl_dir = glm::normalize(pl_dir);
		glm::vec3 moveDelta = pl_dir * pl_movespeed;
		pl_go.transform.position += moveDelta * Timer::DeltaTime();

		/*std::cout << "Delta: " << vec3ToString(moveDelta) << std::endl;
		std::cout << "Position: " << vec3ToString(pl_go.transform.position) << std::endl;*/
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
		
		/*std::cout << "Forward: " << vec3ToString(pl_go.transform.Forward()) << std::endl;
		std::cout << "Right: " << vec3ToString(pl_go.transform.Right()) << std::endl;*/
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		pl_rot.y = 1;
		updateRotation = true;

		/*std::cout << "Forward: " << vec3ToString(pl_go.transform.Forward()) << std::endl;
		std::cout << "Right: " << vec3ToString(pl_go.transform.Right()) << std::endl;*/
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
	}
}

void processPlayerInput(GameObject& pl_go, GLFWwindow* const window)
{
	checkPlayerRotation(pl_go, window);
	checkPlayerMovement(pl_go, window);
}

void drawPlayer(GameObject& pl_go, StaticMesh& pl_sm, unsigned int& transformLoc, Camera& mainCam)
{
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * pl_go.transform.TransformMat4()));
	pl_sm.draw();
}

void processInput(GLFWwindow* window)
{
	if (Input::IsKeyReleased(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		renderSwitch = 1;
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		renderSwitch = 0;*/
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
	Input::Initialise();
	glfwSetKeyCallback(instance->getWindow(), Input::StoreKeyState);

	Shader colShader("shader.vs", "shader.fs");
	Shader textureShader("coltex-shader.vs", "coltex-shader.fs");
	Shader transformShader("transform-coltex-shader.vs", "coltex-shader.fs");


	Line line_z(glm::vec3(0,0,0), glm::vec3(0,0,-50), Colour::Blue());
	Line line_y(glm::vec3(0, 0, 0), glm::vec3(0, 50, 0), Colour::Green());
	Line line_x(glm::vec3(0, 0, 0), glm::vec3(50, 0, 0), Colour::Red());

	//player setup
	GameObject pl_go;
	StaticMesh pl_sm;
	setupPlayer(pl_go, pl_sm);

	//startup the timer
	Timer::tick();
	//int clearConsolePerFrame = 10;

	///attempt to make a view and projection manually

	glm::vec3 camPos, camTarget, camUp;
	//glm::mat4 view = glm::lookAt(, , );

	///

	Camera mainCam;
	mainCam.transform.position = glm::vec3(3, 18, 15);
	//bugged, up orientation is not working
		//due to the lookat function for the camera's view being oriented
		//via the quaternion... updateView uses a global up and works
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

	int maxLines = 5;
	int clearConsolePerFrame = maxLines;
	
	FPSDemo fpsDemo;
	fpsDemo.initialise();

	while (!glfwWindowShouldClose(instance->getWindow()))
	{
		//calculate timing variables
		Timer::tick();
		glfwPollEvents();
		//--clearConsolePerFrame;
		//if (clearConsolePerFrame <= 0)
		//{
		//	system("CLS"); //this is terrabad... don't use it
		//	clearConsolePerFrame = maxLines;
		//}
		//printLine("pos: " + vec3ToString(pl_go.transform.position));
		//printLine("fwd: " + vec3ToString(pl_go.transform.Forward()));
		//printLine("rgt: " + vec3ToString(pl_go.transform.Right()));
		//
		//printLine("deltaTime: " + std::to_string(Timer::DeltaTime()));
		//check input
		processInput(instance->getWindow());
		/*processPlayerInput(pl_go, instance->getWindow());*/

		//updatePlayer(pl_go);
		//render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		fpsDemo.update(Timer::DeltaTime());

		fpsDemo.updateGameObjects();
		//bind
		//colShader.use();
		//textureShader.use();
		//transformShader.use();

		////if (renderSwitch == 0)
		//{
		//	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * s1World));
		//	containerTexture.use();
		//	//draw

		//	stMesh.draw();
		//}
		////else
		//{
		//	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * s2World));
		//	faceTexture.use();

		//	triStMesh.draw();
		//}

		//
		//cubeTran.position = pl_go.transform.position + (pl_go.transform.Forward() * 2.0f);
		//cubeTran.rotate(cubeRotAxis, cubeRotAngle);
		//cubeWorld = transformToMatrix(cubeTran);
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * cubeWorld));
		//containerTexture.use();
		////draw

		//cubeSt.draw();

		//drawPlayer(pl_go, pl_sm,transformLoc, mainCam);
		//
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mainCam.ProjView() * glm::mat4(1)));
		//line_z.draw();
		//line_y.draw();
		//line_x.draw();

		//check for events and swap render buffers
		glfwSwapBuffers(instance->getWindow());
		//Input::RecordKeys();
	}

	glfwTerminate();

	return 0;
}