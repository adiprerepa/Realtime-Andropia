#include "FPS.h"
#include "GameDraw.h"
#include "Input.h"
#include "Texture.h"
#include "UDP.h"
#include "Window.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment (lib, "SDL2/SDL2.lib")
#pragma comment (lib, "SDL2/SDL2main.lib")
#pragma comment (lib, "SDL2/SDL2_image.lib")
#pragma comment (lib, "SDL2/SDL2_ttf.lib")

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
			UDP::send("kd w");
		}
		if (Input::Key::keypress[KEY_A])
		{
			UDP::send("kd a");
		}
		if (Input::Key::keypress[KEY_S])
		{
			UDP::send("kd s");
		}
		if (Input::Key::keypress[KEY_D])
		{
			UDP::send("kd d");
		}
		if (Input::Key::keyrelease[KEY_W])
		{
			UDP::send("ku w");
		}
		if (Input::Key::keyrelease[KEY_A])
		{
			UDP::send("ku a");
		}
		if (Input::Key::keyrelease[KEY_S])
		{
			UDP::send("ku s");
		}
		if (Input::Key::keyrelease[KEY_D])
		{
			UDP::send("ku d");
		}
		if (Input::Mouse::leftclicked)
		{
			UDP::send("mc " + std::to_string(Input::Mouse::pos.x) + " " + std::to_string(Input::Mouse::pos.y));
		}
		if (Input::Mouse::leftclicked)
		{
			UDP::send("mlc " + std::to_string(Input::Mouse::pos.x) + " " + std::to_string(Input::Mouse::pos.y));
		}
		if (Input::Mouse::leftreleased)
		{
			UDP::send("mlr " + std::to_string(Input::Mouse::pos.x) + " " + std::to_string(Input::Mouse::pos.y));
		}

		capFramerate();
	}

	TextureManager::destroy();
	Window::destroy();
	UDP::destroy();
}