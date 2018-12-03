#pragma once

#include "SDL2\SDL_rect.h"

#include <array>
#include <stdint.h>
#include <string.h>
#include <vector>

typedef int texID;

// draw the game state. one half of the client's function
namespace GameDraw
{
	typedef unsigned int ID;

	// object class to store a texture and it's position
	struct obj
	{
		texID t;
		SDL_Rect r;

		void clear()
		{
			memset(this, 0, sizeof(obj));
		}
	};

	// stores the state of the game textures
	struct state
	{
	private:
		// necessary for structure of 'objs' vector. see 'objs'
		int wallcount = 0;

		// stores all objects. obj[0] = player1, obj[1] = player2, obj[2] to obj[wallcount + 2] = walls, objs[wallcount + 3] - objs[float("inf")] = dynamic memory objs
		std::vector<obj> objs;
	public:
		// resize vector to fit at least 2 objs (player1, player2)
		state();

		// update an object with the index ID and with the texID (see TextureManager class in Texture.h) specified. move object to rect r. Set the new size of the objs list to s
		void update(ID i, texID t, SDL_Rect r, unsigned int s);

		// load walls. set wallcount to size of walls. reserve memory in wallobjs for wallcount + 2 (walls + 2 players)
		void loadwalls(std::vector<obj> walls);

		// draw objs
		void draw();
	};


	// run on local machine
	void runlocal();

}
