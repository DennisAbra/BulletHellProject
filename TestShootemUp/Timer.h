#pragma once
#include <SDL.h>

class Timer
{
private:

	static Timer* instance;

	unsigned int startTicks;
	unsigned int elapsedTicks;
	float deltaTime;
	float timeScale;

	Timer();
	~Timer();

public:

	static Timer* Instance();
	static void Release();

	void Reset();
	float DeltaTime();
	void TimeScale(float t);
	float TimeScale();

	void Update();

};
