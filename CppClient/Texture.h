#pragma once

#include "Color.h"

#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"

#include <string>

struct SDL_Texture;

class TextureManager;

typedef int texID;

class Texture
{
private:
	SDL_Point size;

	SDL_Texture * tex = nullptr;

public:

	Texture();
	Texture(SDL_Texture * tex);
	~Texture();

	void load(std::string filename);
	void loadpart(std::string filename, SDL_Rect part);

	void render(SDL_Point pos);
	void render(SDL_Point pos, double theta);
	void render(SDL_Point pos, SDL_Point spincenter, double theta);

	friend TextureManager;
};

class TextureManager
{
public:
	static void init();
	static void destroy();

	static Texture * find(texID ID);

	static void render(texID ID, SDL_Point pos);
	static void render(texID ID, SDL_Point pos, double theta);
	static void render(texID ID, SDL_Point pos, SDL_Point spincenter, double theta);

	static void makeWord(texID ID, std::string text, std::string fontPath, int fontSize, Color forecolor, Color backcolor);

	static void load(texID ID, std::string filename);
	static void loadpart(texID ID, std::string filename, SDL_Rect part);
};