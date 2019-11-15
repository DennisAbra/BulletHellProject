#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity
{
protected:
	SDL_Texture* texture;
	Graphics* graphics;

	int width;
	int height;

	bool clipped;
	SDL_Rect renderRect;
	SDL_Rect clipRect;

public:
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	int GetWidth();
	int GetHeight();
	~Texture();

	virtual void Render();
};