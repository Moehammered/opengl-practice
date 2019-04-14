#ifndef INPUT__H_
#define INPUT__H_

#include <GLFW\glfw3.h>
#include <vector>

class Input
{
public:

	static void Initialise();
	static void RecordKeys();
	static void StoreKeyState(GLFWwindow* window, int key, int scancode,
		int action, int mods);

	static bool IsKeyHeld(int key);
	static bool IsKeyPressed(int key);
	static bool IsKeyReleased(int key);

private:
	Input();
	~Input();

	static Input* const Instance();

	std::vector<int> prevKeyState;
	std::vector<int> currKeyState;

	static Input* _instance;
};

#endif