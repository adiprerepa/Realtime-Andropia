#include "Window.h"

#include "Constants.h"
#include "Input.h"
#include "Texture.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

SDL_Window * WINDOW_WINDOW = nullptr;
SDL_Renderer * WINDOW_RENDERER = nullptr;

void center(SDL_Rect& rect)
{
	rect = { rect.x - rect.w / 2, rect.y - rect.h / 2, rect.w, rect.h };
}

SDL_Texture * Render::createTextureFromSurface(SDL_Surface * surface)
{
	SDL_Texture * t = SDL_CreateTextureFromSurface(WINDOW_RENDERER, surface);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	return t;
}

void Render::drawRect(SDL_Rect rect, Color color)
{
	SDL_SetRenderDrawColor(WINDOW_RENDERER, color.r, color.g, color.b, color.a);
	center(rect);
	SDL_RenderFillRect(WINDOW_RENDERER, &rect);
}

void Render::blit(SDL_Texture * tex, SDL_Rect rect)
{
	center(rect);
	SDL_RenderCopy(WINDOW_RENDERER, tex, nullptr, &rect);
}

void Render::blitEx(SDL_Texture * tex, SDL_Rect rect, double angle, SDL_Point spincenter)
{
	center(rect);
	SDL_RenderCopyEx(WINDOW_RENDERER, tex, nullptr, &rect, angle, &spincenter, SDL_FLIP_NONE);
}

int Window::count = 0;

void Window::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();

	WINDOW_WINDOW = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	WINDOW_RENDERER = SDL_CreateRenderer(WINDOW_WINDOW, -1, SDL_RENDERER_ACCELERATED);

	//SDL_SetRenderDrawBlendMode(WINDOW_RENDERER, SDL_BLENDMODE_BLEND);

	//SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_CaptureMouse(SDL_TRUE);
}

void Window::destroy()
{
	SDL_DestroyWindow(WINDOW_WINDOW);
	SDL_DestroyRenderer(WINDOW_RENDERER);
}

void Window::update()
{
	SDL_RenderPresent(WINDOW_RENDERER);
	SDL_SetRenderDrawColor(WINDOW_RENDERER, 255, 255, 255, 255);
	SDL_RenderClear(WINDOW_RENDERER);
	count++;
}
