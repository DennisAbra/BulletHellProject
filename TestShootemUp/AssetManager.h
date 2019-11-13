#pragma once
#include "Graphics.h"
#include <map>
#include <SDL_mixer.h>


class AssetManager
{

private:
	static AssetManager* instance;
	
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, SDL_Texture*> tex;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> sfx;

	AssetManager();
	~AssetManager();

	std::string GetFullPath(std::string filename);

	TTF_Font* GetFont(std::string filename, int size);

public:

	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(std::string filename);
	SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color);

	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);

};