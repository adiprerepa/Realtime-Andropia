#include "Texture.h"

#include "Constants.h"
#include "Window.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <regex>
#include <vector>

Texture::Texture()
{
	tex = nullptr;
}

Texture::Texture(SDL_Texture * tex)
{
	this->tex = tex;
	SDL_QueryTexture(tex, nullptr, nullptr, &size.x, &size.y);
}

Texture::~Texture()
{
	if (tex) SDL_DestroyTexture(tex);
	tex = nullptr;
}

void Texture::render(SDL_Point pos, bool centered)
{
	Render::blit(tex, { pos.x, pos.y, size.x, size.y }, centered);
}

void Texture::render(SDL_Point pos, double theta, bool centered)
{
	Render::blitEx(tex, { pos.x, pos.y, size.x, size.y }, theta, { pos.x + size.x / 2, pos.y + size.y / 2 }, centered);
}


void Texture::render(SDL_Point pos, SDL_Point spincenter, double theta, bool centered)
{
	Render::blitEx(tex, { pos.x, pos.y, size.x, size.y }, theta, spincenter, centered);
}

void Texture::load(std::string filename)
{
	SDL_Surface * temp = IMG_Load(filename.c_str());

	tex = Render::createTextureFromSurface(temp);

	SDL_FreeSurface(temp);

	SDL_QueryTexture(tex, nullptr, nullptr, &size.x, &size.y);
}

void Texture::loadpart(std::string filename, SDL_Rect part)
{
	SDL_Surface * uncropped = IMG_Load(filename.c_str());
	SDL_Surface * temp = SDL_CreateRGBSurface(uncropped->flags, part.w, part.h, uncropped->format->BitsPerPixel, uncropped->format->Rmask, uncropped->format->Gmask, uncropped->format->Bmask, uncropped->format->Amask);
	SDL_BlitSurface(uncropped, &part, temp, nullptr);

	tex = Render::createTextureFromSurface(temp);

	SDL_FreeSurface(temp);

	SDL_QueryTexture(tex, nullptr, nullptr, &size.x, &size.y);
}

std::vector<std::pair<texID, Texture*>> textures;

void TextureManager::init()
{
}

void TextureManager::destroy()
{
	for (auto& tex : textures)
	{
		tex.second->~Texture();
		delete tex.second;
	}
	textures.clear();
}

Texture * TextureManager::find(texID ID)
{
	for (auto& tex : textures)
	{
		if (tex.first == ID)
		{
			return tex.second;
		}
	}
	return nullptr;
}

void TextureManager::render(texID ID, SDL_Point pos, bool centered)
{
	find(ID)->render(pos, centered);
}

void TextureManager::render(texID ID, SDL_Point pos, double theta, bool centered)
{
	find(ID)->render(pos, theta, centered);
}

void TextureManager::render(texID ID, SDL_Point pos, SDL_Point spincenter, double theta, bool centered)
{
	find(ID)->render(pos, spincenter, theta, centered);
}

extern SDL_Renderer * WINDOW_RENDERER;

void TextureManager::makeWord(texID ID, std::string text, std::string fontPath, int fontSize, Color forecolor, Color backcolor)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

	SDL_Surface* surfaceMessage = TTF_RenderText_Shaded(font, text.c_str(), forecolor.toSDL(), backcolor.toSDL());

	Texture * tex = new Texture(Render::createTextureFromSurface(surfaceMessage));

	textures.push_back({ ID, tex });
}

void TextureManager::load(texID ID, std::string filename)
{
	Texture * tex = new Texture();
	tex->load(filename);
	textures.push_back({ ID, tex });
}

void TextureManager::loadpart(texID ID, std::string filename, SDL_Rect part)
{
	Texture * tex = new Texture();
	tex->loadpart(filename, part);
	textures.push_back({ ID, tex });
}