#ifndef OPENGLLOADER__H_
#define OPENGLLOADER__H_

#include <GLFW\glfw3.h>
#include <string>

class OpenGLLoader
{
public:
	static OpenGLLoader* const Instance();

	void setWindowSize(int x, int y);
	void setWindowResizeEvent(GLFWframebuffersizefun callback);
	bool initialiseOpenGL();
	GLFWwindow* const getWindow();

private:
	OpenGLLoader();
	~OpenGLLoader();

	int glMinorVersion, glMajorVersion, glProfile;
	int screenWidth, screenHeight;
	std::string windowTitle;

	GLFWwindow* windowHandle;
	//singleton instance
	static OpenGLLoader* _instance;
};

#endif