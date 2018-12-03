#include "Input.h"

#include "SDL2/SDL.h"

#include <algorithm>

const unsigned char * Input::Key::key;
bool Input::Key::keypress[256];
bool Input::Key::keyrelease[256];

bool Input::Mouse::leftheld;
bool Input::Mouse::leftclicked;
bool Input::Mouse::leftreleased;
bool Input::Mouse::rightheld;
bool Input::Mouse::rightclicked;
bool Input::Mouse::rightreleased;
SDL_Point Input::Mouse::wheel;
SDL_Point Input::Mouse::pos;

bool Input::closed;

void Input::init()
{
	update();
}

void Input::update()
{
	SDL_Event ev;

	Mouse::leftclicked = false;
	Mouse::rightclicked = false;
	Mouse::leftreleased = false;
	Mouse::rightreleased = false;
	Mouse::wheel = { 0,0 };

	Key::key = SDL_GetKeyboardState(nullptr);

	memset(Key::keypress, 0, sizeof(Key::keypress));
	memset(Key::keyrelease, 0, sizeof(Key::keyrelease));

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{

		case SDL_KEYDOWN:
		{
			// if key not repeating, and keyevent is not SDL_SCANCODE_UNKNOWN, and keyevent is not some weird thing 256 or above
			if (!ev.key.repeat && 4 <= ev.key.keysym.scancode && ev.key.keysym.scancode <= 255)
			{
				Key::keypress[ev.key.keysym.scancode] = true;
			}
			break;
		}

		case SDL_KEYUP:
		{
			// if key not repeating, and keyevent is not SDL_SCANCODE_UNKNOWN, and keyevent is not some weird thing 256 or above
			if (!ev.key.repeat && 4 <= ev.key.keysym.scancode && ev.key.keysym.scancode <= 255)
			{
				Key::keyrelease[ev.key.keysym.scancode] = true;
			}
			break;
		}


		case SDL_MOUSEBUTTONDOWN:
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				Mouse::leftclicked = true;
			}
			if (ev.button.button == SDL_BUTTON_RIGHT)
			{
				Mouse::rightclicked = true;
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				Mouse::leftreleased = true;
			}
			if (ev.button.button == SDL_BUTTON_RIGHT)
			{
				Mouse::rightreleased = true;
			}
			break;
		}

		case SDL_QUIT:
		{
			closed = true;
			break;
		}

		case SDL_MOUSEWHEEL:
		{
			Mouse::wheel = { ev.wheel.x, ev.wheel.y };
		}
		};
	}



	if (Key::keypress[SDL_SCANCODE_ESCAPE])
	{
		closed = true;
	}

	int x, y, z;
	z = SDL_GetMouseState(&x, &y);
	Mouse::pos = { x, y };
	Mouse::leftheld = z & SDL_BUTTON(SDL_BUTTON_LEFT);
	Mouse::rightheld = z & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

std::string Input::toString(Keycode key)
{
	std::string ret = SDL_GetScancodeName(SDL_Scancode(key));
	std::transform(ret.begin(), ret.end(), ret.begin(), [](char c) -> char
	{
		if (c == ' ') return '_'; return toupper(c);
	});
	return "KEY_" + ret;
}
