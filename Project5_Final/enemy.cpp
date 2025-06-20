//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "enemy.h"
#include <iostream>

enemy::enemy()
{
	cirno = al_load_bitmap("cirno_sheet.png");
	cirno_dead = al_load_bitmap("cirno_dead.png");
	live = false;
	speed = 5;

	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 96;
	frameHeight = 128;
	animationColumns = 4;

	hit = al_load_sample("hit.wav");

}
enemy::~enemy()
{
	al_destroy_bitmap(cirno);
	al_destroy_bitmap(cirno_dead);
	al_destroy_sample(hit);

}

void enemy::drawEnemy()
{
	if (live)
	{
		int fx = curFrame * frameWidth;
		int fy = 0;

		al_draw_bitmap_region(cirno, fx, fy, frameWidth, frameHeight, x, y, 0);

	}
	else {
		al_draw_bitmap(cirno_dead, x, y, 0);
	}
}

void enemy::startEnemy(int WIDTH, int HEIGHT)
{
	if (!live)
	{
		if (rand() % 200 == 0)
		{
			live = true;
			x = rand() % (WIDTH - frameWidth);
			y = -100;

		}

	}
}

void enemy::updateEnemy()
{
	y += speed;
	
	if (++frameCount > frameDelay) {
		frameCount = 0;
		if (++curFrame > 3)
			curFrame = 0;
	}

}
void enemy::collideEnemy(player& Player)
{
	if (live && !Player.safe())
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
	if (y > 800)
	{
		live = false;
	}
}