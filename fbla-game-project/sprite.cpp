#include "sprite.h"

Sprite::~Sprite()
{
	UnloadTexture(this->texture);
}

void Sprite::Load(const char* filename, bool updateframes, int frames)
{
	this->updateframes = updateframes;
	this->texture = LoadTexture(filename);
	if (updateframes == true) {
		this->currentframe = 0;
		this->frames = frames;
		this->frame = (Rectangle){ 0.0f, 0.0f, (float)texture.width / frames, (float)texture.height };
	}
}

void Sprite::Update()
{
	currentframe++;

	if (currentframe > frames)
		currentframe = 0;

	frame.x = (float)currentframe * ((float)texture.width / frames);
}

void Sprite::Draw(Vector2 pos)
{
	if (updateframes == true)
		DrawTextureRec(texture, frame, pos, WHITE);
	else
		DrawTextureEx(texture, pos, 0.f, 1.f, WHITE);
}
