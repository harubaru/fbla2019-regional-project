#ifndef LEVEL_H
#define LEVEL_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <raylib.h>
#include "convar.h"
#include "sprite.h"
#include "aabb.h"

struct Enemy {
	int Health;
	int Type;
	bool Delete;
	Vector2 Pos;
};

class Level {
private:
	Sprite sprites[5];
	std::vector<Enemy> enemies;
	int coinrequirement;
	int maxenemies;
	int skeletons;
	int ghosts;
	float offsetx;
public:
	Level() {}
	Level(int coinrequirement, int ghosts, int skeletons);
	~Level();

	void Load(int coinrequirement, int ghosts, int skeletons);
	void Reset();
	void UpdateLevel();
	void DrawLevel();
	bool CheckCollision(Rectangle box);
	bool CheckHit(Rectangle box);
	bool IsFinished();

	int Coins;
	int Health;
};

#endif
