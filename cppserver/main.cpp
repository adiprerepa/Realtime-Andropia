#include <arpa/inet.h>
#include <chrono>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

const int PORT = 55555;

struct gameObject;

const int clientCount = 2;

struct clientData
{
	struct sockaddr_in addr;
	socklen_t addrlen;

	int mousex, mousey;

	bool wkey, akey, skey, dkey;

	gameObject * gobj;

	void connect();
} clients[clientCount];

int sock;
struct sockaddr_in myaddr;
socklen_t myaddrlen = sizeof(myaddr);

struct sockaddr_in remaddr;
socklen_t remaddrlen = sizeof(remaddr);

const int recvbuflen = 1024;
char recvbuf[recvbuflen];
int recvlen;

void * threadID;
pthread_t recvthread;

struct gameObject
{
	int type;
	float x;
	float y;
	float w;
	float h;

	gameObject()
	{

	}

	gameObject(int t, float x, float y, float w, float h) : type(t), x(x), y(y), w(w), h(h)
	{
	}
};

struct gameState
{
	std::vector<gameObject> objs;

	gameState()
	{
		objs.push_back(gameObject(0, 100.0f, 400.0f, 32.0f, 32.0f));

		objs.push_back(gameObject(1, 1180.0f, 400.0f, 32.0f, 32.0f));

		objs.resize(clientCount);

		for (int i = 0; i < clientCount; i++)
		{
			clients[i].gobj = &objs[i];
		}
	}
} mainGameState;

void capFrameRate(int FPS);

inline bool sameAddress(sockaddr_in sockaddr1, sockaddr_in sockaddr2);

void send(int player, std::string data);

void * recvthreadfunction(void *threadid);

void init();

void loop();

void destroy();

int main(int argc, char *argv[])
{
	init();

	for (;;)
	{
		loop();

		capFrameRate(60);
	}
}

void capFrameRate(int FPS)
{
	static std::chrono::steady_clock::time_point frameStart = std::chrono::steady_clock::now();

	std::chrono::steady_clock::duration frameDelay = std::chrono::steady_clock::duration(std::chrono::seconds(1)) / FPS;

	std::this_thread::sleep_until(frameStart + frameDelay);

	frameStart = std::chrono::steady_clock::now();
}

void destroy()
{
	pthread_cancel(recvthread);
	pthread_join(recvthread, &threadID);
	close(sock);
}

void init()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	memset((char *)&myaddr, 0, myaddrlen);
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(PORT);

	bind(sock, (struct sockaddr *)&myaddr, myaddrlen);

	for (;;)
	{
		recvlen = recvfrom(sock, recvbuf, recvbuflen, 0, (struct sockaddr *)&remaddr, &remaddrlen);

		recvbuf[recvlen] = '\0';

		if (!strcmp(recvbuf, "connect"))
		{
			break;
		}

	}

	clients[0].addr = remaddr;
	clients[0].addrlen = remaddrlen;

	printf("client 1 connected from %s:%i\n", inet_ntoa(clients[0].addr.sin_addr), ntohs(clients[0].addr.sin_port));

	for (;;)
	{
		recvlen = recvfrom(sock, recvbuf, recvbuflen, 0, (struct sockaddr *)&remaddr, &remaddrlen);

		recvbuf[recvlen] = '\0';

		if (!strcmp(recvbuf, "connect") && !sameAddress(remaddr, clients[0].addr))
		{
			break;
		}
	}

	clients[1].addr = remaddr;
	clients[1].addrlen = remaddrlen;

	printf("client 2 connected from %s:%i\n", inet_ntoa(clients[1].addr.sin_addr), ntohs(clients[1].addr.sin_port));

	pthread_detach(recvthread);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	pthread_create(&recvthread, NULL, &recvthreadfunction, NULL);
}

void loop()
{
	for (int i = 0; i < clientCount; i++)
	{
		if (clients[i].wkey) clients[i].gobj->y-=3;
		if (clients[i].akey) clients[i].gobj->x-=3;
		if (clients[i].skey) clients[i].gobj->y+=3;
		if (clients[i].dkey) clients[i].gobj->x+=3;
	}

	std::string sendstr;

	for (int i = 0; i < mainGameState.objs.size(); i++)
	{
		gameObject& gobj = mainGameState.objs[i];
		sendstr += std::to_string(i) + " " +
			std::to_string(int(gobj.type)) + " " +
			std::to_string(int(gobj.x)) + " " +
			std::to_string(int(gobj.y)) + " " +
			std::to_string(int(gobj.w)) + " " +
			std::to_string(int(gobj.h)) + " " +
			std::to_string(mainGameState.objs.size()) + " ";
	}

	send(2, sendstr);
}

void * recvthreadfunction(void *threadid)
{
	char datype[10];
	
	for (;;)
	{
		recvlen = recvfrom(sock, recvbuf, recvbuflen, 0, (struct sockaddr *)&remaddr, &remaddrlen);

		recvbuf[recvlen] = '\0';

		std::stringstream ssin(recvbuf);

		memset(datype, 0, sizeof(datype));
		ssin >> datype;

		printf("%s\n", datype);

		for (int i = 0; i < clientCount; i++)
		{
			if (sameAddress(remaddr, clients[i].addr))
			{
				if (!strcmp(datype, "kd"))
				{
					char key;
					ssin >> key;

					if (key == 'w')
					{
						clients[i].wkey = true;
					}
					if (key == 'a')
					{
						clients[i].akey = true;
					}
					if (key == 's')
					{
						clients[i].skey = true;
					}
					if (key == 'd')
					{
						clients[i].dkey = true;
					}
				}
				if (!strcmp(datype, "ku"))
				{
					char key;
					ssin >> key;

					if (key == 'w')
					{
						clients[i].wkey = false;
					}
					if (key == 'a')
					{
						clients[i].akey = false;
					}
					if (key == 's')
					{
						clients[i].skey = false;
					}
					if (key == 'd')
					{
						clients[i].dkey = false;
					}
				}
				if (!strcmp(datype, "mlc"))
				{
					int mx, my;
				}
				if (!strcmp(datype, "mlr"))
				{
					int mx, my;
				}
			}
		}

	}
}

inline bool sameAddress(sockaddr_in sockaddr1, sockaddr_in sockaddr2)
{
	return (sockaddr1.sin_port == sockaddr2.sin_port) && !(strcmp(inet_ntoa(sockaddr1.sin_addr), inet_ntoa(sockaddr2.sin_addr)));
}

void send(int player, std::string data)
{
	if (player == 0)
	{
		sendto(sock, data.c_str(), data.length(), 0, (struct sockaddr *)&clients[0].addr, clients[0].addrlen);
	}
	if (player == 1)
	{
		sendto(sock, data.c_str(), data.length(), 0, (struct sockaddr *)&clients[1].addr, clients[1].addrlen);
	}
	if (player == 2)
	{
		send(0, data);
		send(1, data);
	}
}

