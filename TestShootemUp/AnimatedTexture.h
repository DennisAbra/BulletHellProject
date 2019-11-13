#pragma once
#include "Timer.h"
#include "Texture.h"

class AnimatedTexture : public Texture
{
public:
	enum WRAP_MODE { once = 0, loop = 1 };
	enum ANIM_DIR { horizontal = 0, vertical = 1};

	AnimatedTexture(std::string filename, int x, int y, int w, int h,
		int _frameCount, float _animationSpeed, ANIM_DIR animDirection);
	~AnimatedTexture();

	void WrapMode(WRAP_MODE mode);
	void Update();

private:
	Timer* timer;

	int startX;
	int startY;

	float animationTimer;
	float animationSpeed;
	float timePerFrame;

	int frameCount;

	WRAP_MODE wrapMode;
	ANIM_DIR animationDirection;

	bool animationDone;
};