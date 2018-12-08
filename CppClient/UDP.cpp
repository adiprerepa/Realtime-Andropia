#include "UDP.h"

#include "Constants.h"
#include "GameDraw.h"

#include <sstream>
#include <thread>
#include <WS2tcpip.h>
#include <Winsock2.h>

SOCKET socketC;
struct sockaddr_in serverInfo;
struct addrinfo *thisResult = NULL;
struct addrinfo thisHints;
int serverInfoLen = sizeof(serverInfo);
std::thread thr;

int recvx;
int recvy;


int UDP::receiveThread(GameDraw::state * state)
{
	char recv[recvbufsiz];
	while (1)
	{
		int i = recvfrom(socketC, recv, sizeof(recv), 0, (sockaddr*)&serverInfo, &serverInfoLen);
		if (i != SOCKET_ERROR)
		{
			std::string str(recv, recv + i);

			std::stringstream ss(str);

			GameDraw::ID i; texID t; SDL_Rect r; unsigned int s;

			// decode recieved data. data format is [ID]_[texID]_[x]_[y]_[w]_[h]_[new objs list size]
			while (ss >> i >> t >> r.x >> r.y >> r.w >> r.h >> s)
			{
				// use recieved data
				state->update(i, t, r, s);
			}
		}
		else
		{
		}
	}
}

void UDP::init(GameDraw::state * state)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// sets up client addr, for bind(), and socket()
	ZeroMemory(&thisHints, sizeof(thisHints));
	thisHints.ai_family = AF_INET;
	thisHints.ai_socktype = SOCK_DGRAM;
	thisHints.ai_protocol = IPPROTO_UDP;
	thisHints.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, "", &thisHints, &thisResult);
	socketC = socket(thisResult->ai_family, thisResult->ai_socktype, thisResult->ai_protocol);
	bind(socketC, thisResult->ai_addr, thisResult->ai_addrlen);

	// sets up server addr, for sendto() and recvfrom()
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(serverPort);
	inet_pton(AF_INET, serverIP, &serverInfo.sin_addr.s_addr);

	send("connect");

	// start receive thread
	thr = std::thread(receiveThread, state);
	thr.detach();
}

void UDP::send(std::string str)
{
	sendto(socketC, str.c_str(), str.length(), 0, (sockaddr*)&serverInfo, serverInfoLen);
}

void UDP::destroy()
{
	thr.~thread();
	closesocket(socketC);
}
