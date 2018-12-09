#include "GameDraw.h"
#include "Constants.h"
#include "UDP.h"

#include <sstream>
#include <string.h>
#include <thread>
#if defined _WIN32 || defined _WIN64
#include <WS2tcpip.h>
#include <Winsock2.h>
#elif __APPLE__
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#elif __linux__
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

int socketC;
struct sockaddr_in serverInfo;
struct addrinfo *thisResult = NULL;
struct addrinfo thisHints;
socklen_t serverInfoLen = sizeof(serverInfo);
std::thread thr;

int recvx;
int recvy;

void UDP::receiveThreadFunction(GameDraw::state * state)
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
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	// sets up client addr, for bind(), and socket()
	memset(&thisHints, 0, sizeof(thisHints));
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
	thr = std::thread(receiveThreadFunction);
	thr.detach();
}

void UDP::send(std::string str)
{
	sendto(socketC, str.c_str(), str.length(), 0, (sockaddr*)&serverInfo, serverInfoLen);
}

void UDP::destroy()
{
	thr.~thread();
#ifdef _WIN32
	closesocket(socketC);
#else
	close(socketC);
#endif
}

