#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include "convar.h"

class Sprite {
private:
	Rectangle frame;
	bool updateframes;
	int currentframe;
	int frames;
public:
	Sprite() {}
	Sprite(const char* filename, bool updateframes, int frames) { Load(filename, updateframes, frames); }
	~Sprite();
	void Load(const char* filename, bool updateframes, int frames);
	void Update();
	void Draw(Vector2 pos);

	Texture2D texture;
};

#endif