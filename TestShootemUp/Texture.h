#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity
{
protected:

	Graphics* graphics;
	SDL_Texture* texture;
	int width;
	int height;

	bool clipped;

	SDL_Rect clipRect;

public:
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	int GetWidth();
	int GetHeight();
	~Texture();
	SDL_Rect renderRect;

	virtual void Render();
};