#include "AssetManager.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new AssetManager();
	}

	return instance;
}

void AssetManager::Release()
{
	delete instance;
	instance = nullptr;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (auto tex : textures)
	{
		if (tex.second != NULL)
		{
			SDL_DestroyTexture(tex.second);
		}
	}

	textures.clear();

	for (auto text : tex)
	{
		if (text.second != NULL)
		{
			SDL_DestroyTexture(text.second);
		}
	}

	tex.clear();

	for (auto font : fonts)
	{
		if (font.second != NULL)
		{
			TTF_CloseFont(font.second);
		}
	}

	fonts.clear();

	for (auto m : music)
	{
		if (m.second != NULL)
		{
			Mix_FreeMusic(m.second);
		}
	}

	music.clear();

	for (auto s : sfx)
	{
		if (s.second != NULL)
		{
			Mix_FreeChunk(s.second);
		}
	}

	sfx.clear();
}

std::string AssetManager::GetFullPath(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);
	return fullPath;
}

SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	std::string fullPath = GetFullPath(filename);

	if (textures[fullPath] == nullptr)
	{
		textures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
	}

	return textures[fullPath];
}

TTF_Font* AssetManager::GetFont(std::string filename, int size)
{
	std::string fullPath = GetFullPath(filename);
	std::string key = fullPath + (char)size;

	if (fonts[key] == nullptr)
	{
		fonts[key] = TTF_OpenFont(fullPath.c_str(), size);
		if (fonts[key] == nullptr)
		{
			printf("Error loading font: Font-%s Error-%s", filename.c_str(), TTF_GetError());
		}
	}

	return fonts[key];
}


SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(filename, size);
	
	std::string key = text + filename + (char)size + (char)color.r + (char)color.b +(char)color.g;

	if (tex[key] == nullptr)
	{
		tex[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
	}

	return tex[key];
}

Mix_Music* AssetManager::GetMusic(std::string filename)
{
	std::string fullPath = GetFullPath(filename);

	if (music[fullPath] == nullptr)
	{
		music[fullPath] = Mix_LoadMUS(fullPath.c_str());
		if (music[fullPath] == NULL)
		{
			printf("Music loading error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}

	return music[fullPath];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename)
{
	std::string fullPath = GetFullPath(filename);

	if (sfx[fullPath] == nullptr)
	{
		sfx[fullPath] = Mix_LoadWAV(fullPath.c_str());
		if (sfx[fullPath] == NULL)
		{
			printf("SFX Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}

	return sfx[fullPath];
}
