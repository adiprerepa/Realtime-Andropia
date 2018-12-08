#pragma once

#include <string>

namespace GameDraw
{
	struct state;
}

namespace UDP
{
	int receiveThread(GameDraw::state * state);

	void init(GameDraw::state * state);

	void send(std::string str);

	void destroy();
}