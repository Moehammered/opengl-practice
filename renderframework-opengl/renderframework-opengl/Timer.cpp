#include "Timer.h"

#include <GLFW\glfw3.h>

float Timer::DeltaTime()
{
	return Instance().deltaTime;
}

float Timer::ElapsedTime()
{
	return Instance().currentFrameTime;
}

void Timer::tick()
{
	Instance().currentFrameTime = (float)glfwGetTime();
	Instance().deltaTime = Instance().currentFrameTime - Instance().lastFrameTime;
	Instance().lastFrameTime = Instance().currentFrameTime;
}

Timer::Timer()
{
	currentFrameTime = deltaTime = lastFrameTime = 0;
}


Timer::~Timer()
{
}

Timer & Timer::Instance()
{
	static Timer _instance;
	return _instance;
}
