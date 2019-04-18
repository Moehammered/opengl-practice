#include <glad\glad.h>

#include "OpenGLLoader.h"

OpenGLLoader* OpenGLLoader::_instance = nullptr;

OpenGLLoader* const OpenGLLoader::Instance()
{
	if (!_instance)
		_instance = new OpenGLLoader();

	return _instance;
}

int OpenGLLoader::ScreenWidth()
{
	return screenWidth;
}

int OpenGLLoader::ScreenHeight()
{
	return screenHeight;
}

void OpenGLLoader::setWindowSize(int x, int y)
{
	screenHeight = y;
	screenWidth = x;
}

void OpenGLLoader::setWindowResizeEvent(GLFWframebuffersizefun callback)
{
	if(windowHandle)
		glfwSetFramebufferSizeCallback(windowHandle, callback);
}

bool OpenGLLoader::initialiseOpenGL()
{
	//initialise glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Instance()->glMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Instance()->glMinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, Instance()->glProfile);

	//create the window
	windowHandle = glfwCreateWindow(screenWidth, screenHeight,
		windowTitle.c_str(), nullptr, nullptr);
	if (!windowHandle)
	{
		glfwTerminate();
		return false;
	}

	//make it current
	glfwMakeContextCurrent(windowHandle);

	//load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return false;

	//set the viewport
	glViewport(0, 0, screenWidth, screenHeight);

	return true;
}

GLFWwindow* const OpenGLLoader::getWindow()
{
	return windowHandle;
}

OpenGLLoader::OpenGLLoader()
{
	screenWidth = 800;
	screenHeight = 600;
	glMinorVersion = 3;
	glMajorVersion = 3;
	glProfile = GLFW_OPENGL_CORE_PROFILE;

	windowTitle = "renderframework-opengl";
}


OpenGLLoader::~OpenGLLoader()
{
	glfwDestroyWindow(windowHandle);
	windowHandle = nullptr;
	glfwTerminate();

	if (_instance)
		delete _instance;
	_instance = nullptr;
}
