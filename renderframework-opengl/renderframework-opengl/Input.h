#ifndef INPUT__H_
#define INPUT__H_

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <vector>

class Input
{
public:

	static glm::vec2& const MousePosition();
	static glm::vec2 RawMouseMovementDelta();
	static glm::vec2 NormalisedMouseMovementDelta();
	static void Initialise();
	static void RecordKeys();
	static void RecordMouseMovement();
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
	glm::vec2 mousePos, prevMousePos;

	static Input* _instance;
};

#endif