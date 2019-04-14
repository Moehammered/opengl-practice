#include "Input.h"
#include <iostream>

Input* Input::_instance = nullptr;
//std::vector<int> Input::prevKeyState;
//std::vector<int> Input::currKeyState;

void Input::Initialise()
{
	//Input in = Instance();
	std::cout << "init input" << std::endl;
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

void Input::StoreKeyState(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Input* in = Instance();
	//in.prevKeyState = in.currKeyState;
	std::cout << std::endl;
	in->prevKeyState[key] = in->currKeyState[key];
	in->currKeyState[key] = action;
	std::cout << "Key(" << key << ") state(" << action << ")" << std::endl;
	std::cout << "CurrKey(" << key << ") Currstate(" << in->currKeyState[key] << ")" << std::endl;
	std::cout << "PrevKey(" << key << ") Prevstate(" << in->prevKeyState[key] << ")" << std::endl;
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
	std::cout << "input destroy" << std::endl;
}

Input * const Input::Instance()
{
	if (!_instance)
		_instance = new Input();

	return _instance;
}
