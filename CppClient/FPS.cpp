#include "FPS.h"

#include "Constants.h"

#include <chrono>
#include <thread>

// wait until framerate goody
void capFramerate()
{
	using namespace std::chrono_literals;

	static std::chrono::steady_clock::time_point frameStart = std::chrono::steady_clock::now();

	auto frameDelay = std::chrono::steady_clock::duration(1s) / FPS;

	std::this_thread::sleep_until(frameStart + frameDelay);

	frameStart = std::chrono::steady_clock::now();
}
