#include "level.h"

static float randompos(float low, float high)
{
	return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

Level::Level(int coinrequirement, int ghosts, int skeletons)
{
	Load(coinrequirement, ghosts, skeletons);
}

Level::~Level()
{
}

void Level::Load(int coinrequirement, int ghosts, int skeletons)
{
	this->Health = 3;
	this->Coins = 0;
	this->coinrequirement = coinrequirement;
	this->maxenemies = ghosts + skeletons;
	this->ghosts = ghosts;
	this->skeletons = skeletons;

	enemies.reserve(maxenemies);

	sprites[0].Load("res/textures/mapobjects/ghost.png", true, 3);
	sprites[1].Load("res/textures/mapobjects/skeleton.png", true, 3);

	srand(static_cast<unsigned>(time(0)));

	int sghosts = 0;
	int sskeletons = 0;

	for (int i = 0; i < maxenemies; i++) {
		Enemy newenemy;
		newenemy.Delete = false;
		newenemy.Pos.x = randompos(E_SPAWN_XLO, E_SPAWN_XHI);
		newenemy.Pos.y = randompos(E_SPAWN_YLO, E_SPAWN_YHI);
		if (sghosts < ghosts) {
			newenemy.Type = 0;
			newenemy.Health = 2;
			sghosts++;
		} else if (sskeletons < skeletons) {
			newenemy.Type = 1;
			newenemy.Health = 3;
		}
		enemies.push_back(newenemy);
	}
}

void Level::Reset()
{
	this->Health = 3;
	this->Coins = 0;

	enemies.clear();
	enemies.reserve(maxenemies);

	srand(static_cast<unsigned>(time(0)));

	int sghosts = 0;
	int sskeletons = 0;

	for (int i = 0; i < maxenemies; i++) {
		Enemy newenemy;
		newenemy.Delete = false;
		newenemy.Pos.x = randompos(E_SPAWN_XLO, E_SPAWN_XHI);
		newenemy.Pos.y = randompos(E_SPAWN_YLO, E_SPAWN_YHI);
		if (sghosts < ghosts) {
			newenemy.Type = 0;
			newenemy.Health = 2;
			sghosts++;
		}
		else if (sskeletons < skeletons) {
			newenemy.Type = 1;
			newenemy.Health = 3;
		}
		enemies.push_back(newenemy);
	}
}

void Level::UpdateLevel()
{
	for (auto& i : enemies) {
		if (i.Pos.x < -75) {
			i.Pos.x = randompos(E_SPAWN_XLO, E_SPAWN_XHI);
			i.Pos.y = randompos(E_SPAWN_YLO, E_SPAWN_YHI);
		}
		i.Pos.x -= 8.f;
	}
}

void Level::DrawLevel()
{
	for (auto& i : enemies) {
		if (i.Delete)
			continue;
		sprites[i.Type].Draw((Vector2) { i.Pos.x, i.Pos.y });
	}
}

bool Level::CheckCollision(Rectangle box)
{

	for (auto& i : enemies) {
		if (i.Delete)
			continue;

		Rectangle ecoll;
		ecoll.x = i.Pos.x;
		ecoll.y = i.Pos.y;
		ecoll.height = 104;
		ecoll.width = 104;

		if (aabb_quad_intersect(box, ecoll) == true) {
			i.Pos.x = randompos(E_SPAWN_XLO, E_SPAWN_XHI);
			i.Pos.y = randompos(E_SPAWN_YLO, E_SPAWN_YHI);
			return true;
		}
	}

	return false;
}

bool Level::CheckHit(Rectangle box)
{
	for (auto& i : enemies) {
		if (i.Delete)
			continue;

		Rectangle ecoll;
		ecoll.x = i.Pos.x;
		ecoll.y = i.Pos.y;
		ecoll.height = 104;
		ecoll.width = 104;

		if (aabb_quad_intersect(box, ecoll) == true) {
			if ((Coins < coinrequirement) && (i.Health == 0)) {
				if (Health < 3)
					Health++;
				Coins++;
				i.Delete = true;
			} else {
				i.Health--;
			}
			if (Health < 3)
				Health++;
			return true;
		}
	}
	return false;
}

bool Level::IsFinished()
{
	if (Coins == coinrequirement)
		return true;

	return false;
}
