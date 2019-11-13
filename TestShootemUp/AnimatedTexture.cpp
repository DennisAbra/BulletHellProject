#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int _frameCount, float _animationSpeed, ANIM_DIR animDirection)
	: Texture(filename, x, y, w, h)
{
	timer = Timer::Instance();

	startX = x;
	startY = y;

	frameCount = _frameCount;
	animationSpeed = _animationSpeed;
	timePerFrame = animationSpeed / frameCount;
	animationTimer = 0.0f;

	animationDirection = animDirection;

	animationDone = false;

	wrapMode = loop;
}

AnimatedTexture::~AnimatedTexture()
{
}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
	wrapMode = mode;
}

void AnimatedTexture::Update()
{
	if (!animationDone)
	{
		animationTimer += timer->DeltaTime();

		if (animationTimer >= animationSpeed)
		{
			if (wrapMode == loop)
			{
				animationTimer -= animationSpeed;
			}
			else
			{
				animationDone = true;
				animationTimer = animationSpeed - timePerFrame;
			}
		}

		if (animationDirection == horizontal)
		{
			clipRect.x = startX + (int)(animationTimer / timePerFrame) * width;
		}
		else
		{
			clipRect.y = startY + (int)(animationTimer / timePerFrame) * height;
		}
	}
}
