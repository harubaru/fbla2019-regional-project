#include <stdio.h>
#include "game.h"

void Game::bgdraw()
{
	for (int i = 0; i < 4; i++) {
		DrawTextureEx(parallax[i], (Vector2){ parallax_scroll[i], 0 }, 0.0f, 1.0f, WHITE);
		DrawTextureEx(parallax[i], (Vector2){ (parallax[i].width) + parallax_scroll[i], 0 }, 0.0f, 1.0f, WHITE);
		DrawTextureEx(parallax[i], (Vector2){ (-parallax[i].width) + parallax_scroll[i], 0 }, 0.0f, 1.0f, WHITE);
	}
}

void Game::bgscroll(int direction) // -1 = backward, 0 = none, 1 = forward
{
	if (direction < 0) {
		parallax_scroll[0] += 0.4f;
		parallax_scroll[1] += 1.0f;
		parallax_scroll[2] += 2.0f;
		parallax_scroll[3] += 4.0f;
	} else if (direction > 0) {
		parallax_scroll[0] -= 0.4f;
		parallax_scroll[1] -= 1.0f;
		parallax_scroll[2] -= 2.0f;
		parallax_scroll[3] -= 4.0f;
	}



	for (int i = 0; i < 4; i++) {
		if (parallax_scroll[i] <= -parallax[i].width * 1) 
			parallax_scroll[i] = 0.f;
		if (parallax_scroll[i] >= parallax[i].width * 1)
			parallax_scroll[i] = 0.f;
	}
}

void Game::spriteupdater()
{
	static int framecounter = 0;
	framecounter++;
	if (framecounter >= (60 / FRAME_SPEED)) {
		// Update Sprites!
		framecounter = 0;
		player.Update();

		for (int i = 0; i < 2; i++)
			enemies[i].Update();
	}
}

void Game::pfire()
{
	if (hasFired == false) {
		hasFired = true;
		bx = px + P_BEAM_XOFFSET;
		by = py + P_BEAM_YOFFSET;
	}
}

void Game::pupdate()
{
	if (hasFired == true) {
		bx += 32.f;
		if (bx > (px + 500 + P_BEAM_XOFFSET))
			hasFired = false;
		else {
			beam.Draw((Vector2) { (float)bx, (float)by });
			Rectangle beamcoll;
			beamcoll.x = bx;
			beamcoll.y = by;
			beamcoll.width = 64;
			beamcoll.height = 12;
			if (level[currentlevel].CheckHit(beamcoll) == true)
				hasFired = false;
		}
	}
}

void Game::input()
{
	if (IsKeyPressed(KEY_ESCAPE)) this->gstate = QUIT;

	if (gstate == MAINMENU) {
		Rectangle startbutton;
		startbutton.x = 436.f;
		startbutton.y = 183.f;
		startbutton.height = 104.f;
		startbutton.width = 213.f;

		Rectangle quitbutton;
		quitbutton.x = 421.f;
		quitbutton.y = 331.f;
		quitbutton.height = 87.f;
		quitbutton.width = 213.f;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 pos = GetMousePosition();
			if (aabb_point_intersect(pos, startbutton)) {
				gstate = RUNNING;
			} else if (aabb_point_intersect(pos, quitbutton)) {
				gstate = QUIT;
			}
		}
	}

	if (gstate == LEVELED) {
		if (currentlevel != 4) {
			Rectangle nextbutton;
			nextbutton.x = 382.f;
			nextbutton.y = 370.f;
			nextbutton.height = 200;
			nextbutton.width = 297;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				Vector2 pos = GetMousePosition();
				if (aabb_point_intersect(pos, nextbutton)) {
					currentlevel++;
					gstate = RUNNING;
				}
			}
		}
	}

	if (gstate == LOST) {
		Rectangle lostbutton;
		lostbutton.x = 346.f;
		lostbutton.y = 394.f;
		lostbutton.height = 184;
		lostbutton.width = 312;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 pos = GetMousePosition();
			if (aabb_point_intersect(pos, lostbutton)) {
				level[currentlevel].Reset();
				gstate = RUNNING;
			}
		}
	}

	if (gstate == RUNNING) {
		if (IsKeyDown(KEY_TAB))
			gstate = MAINMENU;
		if (IsKeyDown(KEY_W)) {
			if (py >= -32.f) {
				py -= P_MOVEMENT;
			}
		}
		if (IsKeyDown(KEY_S)) {
			if (py <= 556.f) {
				py += P_MOVEMENT;
			}
		}
//		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		if (IsKeyPressed(KEY_SPACE))
			pfire();

		level[currentlevel].UpdateLevel();

		Rectangle playercoll;
		playercoll.x = px;
		playercoll.y = py;
		playercoll.height = 120;
		playercoll.width = 96;

		if (level[currentlevel].CheckCollision(playercoll)) {
			if (level[currentlevel].Health == 0) {
				gstate = LOST;
			} else {
				level[currentlevel].Health--;
			}
		}
	}
}

void Game::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	bgdraw();

	switch (this->gstate) {
	case RUNNING:
		bgscroll(1);
		player.Draw((Vector2) { px, py });
		pupdate();
		level[currentlevel].DrawLevel();
		DrawText(FormatText("Lives: %i\nScore: %i\n", level[currentlevel].Health, level[currentlevel].Coins), 15, HEIGHT - 100, 30, WHITE);
		DrawText(FormatText("Level: %i\n", currentlevel), 15, 30, 30, WHITE);
		break;
	case LEVELED:
		bgscroll(1);
		if (currentlevel != 4) {
			DrawTextureEx(nextmenu, (Vector2) { 0.f, 0.f }, 0.f, 1.f, WHITE);
			DrawText(FormatText("Top Score: %i\n", TotalCoins), (WIDTH / 2) - 100, (HEIGHT / 2) - 50, 30, WHITE);
		}
		else {
			DrawTextureEx(gratmenu, (Vector2) { 0.f, 0.f }, 0.f, 1.f, WHITE);
			DrawText(FormatText("Top Score: %i\n", TotalCoins), (WIDTH / 2) - 100, (HEIGHT / 2) + 50, 30, WHITE);
		}
		break;
	case LOST:
		bgscroll(1);
		DrawTextureEx(rtrymenu, (Vector2) { 0.f, 0.f }, 0.f, 1.f, WHITE);
		DrawText(FormatText("Top Score: %i\n", TotalCoins), (WIDTH / 2) - 100, (HEIGHT / 2) - 50, 30, WHITE);
		break;
	case MAINMENU:
		bgscroll(1);
		DrawTextureEx(mainmenu, (Vector2) { 0.f, 0.f }, 0.f, 1.f, WHITE);
		break;
	case QUIT:
		EndDrawing();
		CloseWindow();
		return;
	}

	EndDrawing();
}

void Game::run()
{
	InitWindow(WIDTH, HEIGHT, TITLE_STR);
	SetTargetFPS(60);

	mainmenu = LoadTexture("res/textures/koishiititle.png");
	nextmenu = LoadTexture("res/textures/next.png");
	rtrymenu = LoadTexture("res/textures/tryagain.png");
	gratmenu = LoadTexture("res/textures/congratz.png");

	parallax[0] = LoadTexture("res/textures/parallax/background.png");
	parallax[1] = LoadTexture("res/textures/parallax/background-light.png");
	parallax[2] = LoadTexture("res/textures/parallax/middle.png");
	parallax[3] = LoadTexture("res/textures/parallax/front.png");

	for (int i = 0; i < 4; i++)
		parallax_scroll[i] = 0.f;

	player.Load("res/textures/mapobjects/bat.png", true, 3);
	beam.Load("res/textures/mapobjects/beam.png", false, 0);

	currentlevel = 0;
	TotalCoins = 0;

	level[0].Load(5, 5, 3);
	level[1].Load(7, 4, 4);
	level[2].Load(10, 5, 7);
	level[3].Load(15, 10, 8);
	level[4].Load(20, 10, 15);

	while (!WindowShouldClose()) {
		if (gstate == QUIT)
			break;

		spriteupdater();
		input();
		render();

		if (level[currentlevel].IsFinished()) {
			gstate = LEVELED;
			TotalCoins += level[currentlevel].Coins;
			level[currentlevel].Coins = 0;
		}
	}

	for (int i = 0; i < 4; i++)
		UnloadTexture(parallax[i]);

	CloseWindow();
}
