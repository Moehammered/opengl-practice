#ifndef TIMER__H_
#define TIMER__H_

class Timer
{
public:
	static float DeltaTime();
	static float ElapsedTime();
	static void tick();

private:
	Timer();
	~Timer();

	static Timer& Instance();

	float lastFrameTime, currentFrameTime, deltaTime;
};

#endif