//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "boss.h"
#include <iostream>

boss::boss()
{
	x = 400;
	y = 0;
	remilia = al_load_bitmap("remilia_sheet.png");
	remilia_dead = al_load_bitmap("dead.png");
	alive = false;
	lives = 500;
	speed = 5;
	state = DOWN;
	pauseTimer = 0;
	
	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 96;
	frameHeight = 120;
	animationColumns = 4;

	hit = al_load_sample("hit.wav");

}
boss::~boss()
{
	al_destroy_bitmap(remilia);
	al_destroy_bitmap(remilia_dead);
	al_destroy_sample(hit);
}

void boss::drawBoss()
{
	if (alive && lives >= 1)
	{
		int fx = curFrame * frameWidth;
		int fy = 0;

		al_draw_bitmap_region(remilia, fx, fy, frameWidth, frameHeight, x, y, 0);
	}
	else {
		al_draw_bitmap(remilia_dead, x, y, 0);
	}
}

//summons boss above the screen for a dramatic entrance
void boss::startBoss(int WIDTH, int HEIGHT)
{
	if (!alive) {
		alive = true;
		x = (WIDTH / 2) - frameWidth / 2;
		y = -800;
	}
}

//	makes the boss first move down until somewhere below the bottom of the screen at first.
//	boss then moves all the way to the left, pauses for a bit, then all the way to the right, pauses
//	boss then repeats, going back to the left
void boss::updateBoss()
{

	switch (state) {
	case DOWN:
		y += speed;
		if (y >= 100) {
			y = 100;
			state = LEFT;
		}
		break;
	case LEFT:
		x -= speed;
		if (x <= 0) {
			x = 0;
			state = PAUSELEFT;
			pauseTimer = 60; // pauses for 60 frames, or 1 second
		}
		break;
	case PAUSELEFT:
		if (--pauseTimer <= 0) {
			state = RIGHT;
		}
		break;
	case RIGHT:
		x += speed;
		if (x >= 800 - frameWidth) {
			x = 800 - frameWidth;
			state = PAUSERIGHT;
			pauseTimer = 60; // 1 second pause
		}
		break;
	case PAUSERIGHT:
		if (--pauseTimer <= 0) {
			state = LEFT;
		}
		break;
	}

	//animation
	if (++frameCount > frameDelay) {
		frameCount = 0;
		if (++curFrame > 3)
			curFrame = 0;
	}

}
//checks if the player ran into the boss
void boss::collideBoss(player& Player)
{
	if (alive && !Player.safe())
	{
		if (x - frameWidth / 2 < Player.getX() + Player.getWidth() / 2 &&
			x + frameWidth / 2 > Player.getX() - Player.getWidth() / 2 &&
			y - frameHeight / 2 < Player.getY() + Player.getHeight() / 2 &&
			y + frameHeight / 2 > Player.getY() - Player.getHeight() / 2)
		{
			Player.removeLife();
			Player.setiframes();
			Player.setiframeTimer();
			al_play_sample(hit, 1.0, 0.0, 0.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}
}