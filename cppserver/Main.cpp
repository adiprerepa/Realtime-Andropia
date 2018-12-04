#include <conio.h>
#include <sstream>
#include <thread>
#include <WS2tcpip.h>
#include <Winsock2.h>

#pragma comment (lib, "ws2_32.lib")

const int recvbufsiz = 1024;
char recv[recvbufsiz];

SOCKET socketC;

struct sockaddr_in thisaddr;
int thislen = sizeof(thisaddr);

std::thread thr;

struct sockaddr_in client1;
struct sockaddr_in client2;
struct sockaddr_in from;
int fromlen = sizeof(from);
int client1len;
int client2len;


int receiveThread()
{
	while (1)
	{
		memset(recv, 0, sizeof(recv));
		int i = recvfrom(socketC, recv, sizeof(recv), 0, (sockaddr*)&from, &fromlen);
		if (i != SOCKET_ERROR)
		{
			std::string str(recv, recv + i);

			if ((from.sin_addr.s_addr == client1.sin_addr.s_addr) && (from.sin_port == client1.sin_port))
			{
			}
			if ((from.sin_addr.s_addr == client2.sin_addr.s_addr) && (from.sin_port == client2.sin_port))
			{

			}
		}
	}
}

void init()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	socketC = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	thisaddr.sin_family = AF_INET;
	thisaddr.sin_port = htons(55555);
	inet_pton(AF_INET, "127.0.0.1", &thisaddr.sin_addr.s_addr);

	bind(socketC, (SOCKADDR *) &thisaddr, thislen);

	recvfrom(socketC, recv, sizeof(recv), 0, (sockaddr*)&client1, &client1len);

	do
	{
		recvfrom(socketC, recv, sizeof(recv), 0, (sockaddr*)&client1, &client1len);
	} while ((client1.sin_addr.s_addr == client1.sin_addr.s_addr) && (client1.sin_port == client2.sin_port));
	


	thr = std::thread(receiveThread);
	thr.detach();
}

void send(std::string str, int player)
{
	if (player == 1)
	{
		if (sendto(socketC, str.c_str(), str.length(), 0, (sockaddr*)&client1, client1len) != SOCKET_ERROR)
		{
			printf("send to 1: %s", str.c_str());
		}
	}
	if (player == 2)
	{
		if (sendto(socketC, str.c_str(), str.length(), 0, (sockaddr*)&client2, client2len) != SOCKET_ERROR)
		{
			printf("send to 1: %s", str.c_str());
		}
	}
	if (player == 3)
	{
		if (sendto(socketC, str.c_str(), str.length(), 0, (sockaddr*)&client1, client1len) != SOCKET_ERROR)
		{
			if (sendto(socketC, str.c_str(), str.length(), 0, (sockaddr*)&client2, client2len) != SOCKET_ERROR)
			{
				printf("send to 1 and 2: %s", str.c_str());
			}
		}
	}
}

void destroy()
{
	thr.~thread();
	closesocket(socketC);
}


int main()
{
	init();
	while (true)
	{
		send("hello", 3);

		char c = _getch();

		if (c == 'c')
		{
			break;
		}
	}
	destroy();
}
