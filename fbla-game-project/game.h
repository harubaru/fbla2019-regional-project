#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "convar.h"
#include "sprite.h"
#include "level.h"
#include "aabb.h"

enum GameState {
	RUNNING,
	LEVELED,
	LOST,
	MAINMENU,
	QUIT
};

class Game {
private:
	// resources
	Texture2D mainmenu;
	Texture2D nextmenu;
	Texture2D rtrymenu;
	Texture2D gratmenu;
	Texture2D parallax[4];
	float parallax_scroll[4];

	Sprite player;
	Sprite beam;
	
	float bx, by;
	bool hasFired;
	Sprite enemies[2];
	float px, py;

	Level level[6];
	int currentlevel;
	int TotalCoins;

	// functions
	void bgdraw();
	void bgscroll(int direction);
	void spriteupdater();
	void pfire();
	void pupdate();

	void input();
	void render();

	GameState gstate;
public:
	Game() : gstate(MAINMENU), px(P_INIT_STARTX), py(P_INIT_STARTH), bx(P_INIT_STARTX), by(P_INIT_STARTH), hasFired(false) {  }
	void run();
};

#endif