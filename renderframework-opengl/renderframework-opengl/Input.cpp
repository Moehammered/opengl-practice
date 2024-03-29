#include "Input.h"
#include "OpenGLLoader.h"
#include <iostream>
#include "HelperFunctions.h"
#include "TransformHelperFunctions.h"

Input* Input::_instance = nullptr;
//std::vector<int> Input::prevKeyState;
//std::vector<int> Input::currKeyState;

glm::vec2 & const Input::MousePosition()
{
	return Instance()->mousePos;
}

glm::vec2 Input::RawMouseMovementDelta()
{
	return Instance()->mousePos - Instance()->prevMousePos;
}

glm::vec2 Input::NormalisedMouseMovementDelta()
{
	glm::vec2 raw = Input::RawMouseMovementDelta();

	raw.x /= (float)OpenGLLoader::Instance()->ScreenWidth();
	raw.y /= (float)OpenGLLoader::Instance()->ScreenHeight();

	return raw;
}

void Input::Initialise()
{
	//Input in = Instance();
	#if INPUT_VERBOSEOUTPUT == 1
		std::cout << "init input" << std::endl;
	#endif
	Instance()->prevKeyState.resize(GLFW_KEY_LAST + 1);
	Instance()->currKeyState.resize(GLFW_KEY_LAST + 1);
}

void Input::RecordKeys()
{
	Input* in = Instance();
	for (int i = 0; i < in->prevKeyState.size(); ++i)
	{
		in->prevKeyState[i] = in->currKeyState[i];
	}
	//in.prevKeyState.assign(in.currKeyState.begin(), in.currKeyState.end());
}

void Input::RecordMouseMovement()
{
	Input* in = Instance();
	double x, y;
	in->prevMousePos = in->mousePos;
	glfwGetCursorPos(OpenGLLoader::Instance()->getWindow(), &x, &y);

	in->mousePos.x = x;
	in->mousePos.y = y;
}

void Input::StoreKeyState(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Input* in = Instance();
	//in.prevKeyState = in.currKeyState;
	if (key < 0)
		return;
	in->prevKeyState[key] = in->currKeyState[key];
	in->currKeyState[key] = action;
	#if INPUT_VERBOSEOUTPUT == 1
		std::cout << std::endl;
		std::cout << "Key(" << key << ") state(" << action << ")" << std::endl;
		std::cout << "CurrKey(" << key << ") Currstate(" << in->currKeyState[key] << ")" << std::endl;
		std::cout << "PrevKey(" << key << ") Prevstate(" << in->prevKeyState[key] << ")" << std::endl;
	#endif
}

bool Input::IsKeyHeld(int key)
{
	return Instance()->currKeyState[key] == GLFW_PRESS || Instance()->currKeyState[key] == GLFW_REPEAT;
}

bool Input::IsKeyPressed(int key)
{
	Input* in = Instance();
	bool result = false;
	
	result = in->currKeyState[key] == GLFW_PRESS;
	result = result && (in->prevKeyState[key] != GLFW_PRESS);

	return result;
}

bool Input::IsKeyReleased(int key)
{
	Input* in = Instance();
	bool result = false;

	result = in->currKeyState[key] == GLFW_RELEASE;
	result = result && (in->prevKeyState[key] != GLFW_RELEASE);

	return result;
}

Input::Input()
{
	/*prevKeyState.resize(GLFW_KEY_LAST + 1);
	currKeyState.resize(GLFW_KEY_LAST + 1);

	std::cout << "init input" << std::endl;*/
}

Input::~Input()
{
	#if INPUT_VERBOSEOUTPUT == 1
		std::cout << "input destroy" << std::endl;
	#endif
	delete _instance;
}

Input * const Input::Instance()
{
	if (!_instance)
		_instance = new Input();

	return _instance;
}
