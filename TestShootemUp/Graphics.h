#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Graphics
{
public:
	static const int screenWidth = 800;
	static const int screenHeight = 600;

	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	void Render();

	SDL_Texture* LoadTexture(std::string path);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	void ClearBackBuffer();

	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void DrawLine(float startX, float startY, float endX, float endY);

private:
	static Graphics* instance;
	static bool initialized;

	SDL_Window* window;
	SDL_Surface* backBuffer;

	SDL_Renderer* renderer;

	Graphics();
	~Graphics();
	bool Init();
};
