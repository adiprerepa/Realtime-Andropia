#include "FPS.h"
#include "GameDraw.h"
#include "Input.h"
#include "Texture.h"
#include "UDP.h"
#include "Window.h"

#include <Windows.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment (lib, "SDL2/SDL2.lib")
#pragma comment (lib, "SDL2/SDL2main.lib")
#pragma comment (lib, "SDL2/SDL2_image.lib")
#pragma comment (lib, "SDL2/SDL2_ttf.lib")

HWND Stealth = FindWindowA("ConsoleWindowClass", NULL);

GameDraw::state state;

int main()
{
	// window go bye bye for later when not debugging
	//ShowWindow(Stealth, 0);

	Window::init();
	Input::init();
	TextureManager::init();
	UDP::init(&state);

	while (!Input::closed)
	{
		Input::update();

		state.draw();

		Window::update();

		if (Input::Key::keypress[KEY_W])
		{
			UDP::send("wp");
		}
		if (Input::Key::keypress[KEY_A])
		{
			UDP::send("ap");
		}
		if (Input::Key::keypress[KEY_S])
		{
			UDP::send("sp");
		}
		if (Input::Key::keypress[KEY_D])
		{
			UDP::send("dp");
		}
		if (Input::Key::keyrelease[KEY_W])
		{
			UDP::send("wr");
		}
		if (Input::Key::keyrelease[KEY_A])
		{
			UDP::send("ar");
		}
		if (Input::Key::keyrelease[KEY_S])
		{
			UDP::send("sr");
		}
		if (Input::Key::keyrelease[KEY_D])
		{
			UDP::send("dr");
		}

		capFramerate();
	}

	TextureManager::destroy();
	Window::destroy();
	UDP::destroy();
	ShowWindow(Stealth, 1);
}
