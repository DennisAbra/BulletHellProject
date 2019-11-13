#include "Graphics.h"

Graphics* Graphics::instance = nullptr;
bool Graphics::initialized = false;

Graphics* Graphics::Instance()
{
	if (instance == nullptr)
	{
		instance = new Graphics();
	}

	return instance;
}

void Graphics::Release()
{
	delete instance;
	instance = nullptr;

	initialized = false;
}

bool Graphics::Initialized()
{
	return initialized;
}

Graphics::Graphics()
{
	backBuffer = nullptr;
	initialized = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL Initialization Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Super crappy Mega Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window Creation Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer creation error: %s\n", SDL_GetError());
		return false;
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		printf("Error IMG initialization %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF init failure: %s\n", TTF_GetError());
		return false;
	}

	backBuffer = SDL_GetWindowSurface(window);

	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string path)
{
	SDL_Texture* tex = nullptr;

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		printf("Image Load Error: Path(%s)\n - Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}

	tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL)
	{
		printf("Error when creating Texture: %s \n", SDL_GetError());
		return tex;
	}
	SDL_FreeSurface(surface);
	return tex;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL)
	{
		printf("Text Render Error: %s\n", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL)
	{
		printf("Text Texture creation failed: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(surface);

	return tex;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(renderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, tex, clip, rend, angle, NULL, flip);
}

void Graphics::DrawLine(float startX, float startY, float endX, float endY)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Graphics::Render()
{
	SDL_RenderPresent(renderer);
}

