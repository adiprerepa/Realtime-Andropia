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

	void render(SDL_Point pos, bool centered);
	void render(SDL_Point pos, double theta, bool centered);
	void render(SDL_Point pos, SDL_Point spincenter, double theta, bool centered);

	void load(std::string filename);
	void loadpart(std::string filename, SDL_Rect part);

	friend TextureManager;
};

class TextureManager
{
public:
	static void init();
	static void destroy();

	static Texture * find(texID ID);

	static void render(texID ID, SDL_Point pos, bool centered);
	static void render(texID ID, SDL_Point pos, double theta, bool centered);
	static void render(texID ID, SDL_Point pos, SDL_Point spincenter, double theta, bool centered);

	static void load(texID ID, std::string filename);
	static void loadpart(texID ID, std::string filename, SDL_Rect part);

	static void makeWord(texID ID, std::string text, std::string fontPath, int fontSize, Color forecolor, Color backcolor);
};