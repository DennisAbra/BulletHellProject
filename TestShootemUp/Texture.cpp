#include "Texture.h"

Texture::Texture(std::string filename)
{
	graphics = Graphics::Instance();

	texture = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	clipped = false;

	renderRect.w = width;
	renderRect.h = height;
}

Texture::Texture(std::string filename, int x, int y, int w, int h)
{
	graphics = Graphics::Instance();

	texture = AssetManager::Instance()->GetTexture(filename);

	clipped = true;

	width = w;
	height = h;

	renderRect.w = width;
	renderRect.h = height;

	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = width;
	clipRect.h = height;

}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
{
	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetText(text, fontPath, size, color);

	clipped = false;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	renderRect.w = width;
	renderRect.h = height;
}

Texture::~Texture()
{
	texture = nullptr;
	graphics = nullptr;
}

void Texture::Render()
{
	Vector2 pos = Pos(world);
	Vector2 scale = Scale(world);

	renderRect.x = (int)(pos.x - width * scale.x * 0.5f);
	renderRect.y = (int)(pos.y - height * scale.y * 0.5f);
	renderRect.w = (int)(width * scale.x);
	renderRect.h = (int)(height * scale.y);

	graphics->DrawTexture(texture,(clipped)? &clipRect : NULL, &renderRect, Rotation(world));
}