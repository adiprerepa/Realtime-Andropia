#pragma once

#include <string>

namespace GameDraw
{
	struct state;
}

namespace UDP
{
	void receiveThreadFunction(GameDraw::state * state);

	void verificationPacketThreadFunction();

	void init(GameDraw::state * state);

	void send(std::string str);

	void destroy();
}

