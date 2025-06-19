//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "boss.h"
#include <iostream>

boss::boss()
{
	cirno = al_load_bitmap("cirno_sheet.png");
	cirno_dead = al_load_bitmap("cirno_dead.png");
	live = false;
	collided = false;
	speed = 5;
	/*boundx = al_get_bitmap_width(cirno) * .5;
	boundy = al_get_bitmap_height(cirno) * .5;*/

	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 96;
	frameHeight = 128;
	animationColumns = 4;

}
boss::~boss()
{
	al_destroy_bitmap(cirno);
	al_destroy_bitmap(cirno_dead);
}

void boss::drawBoss()
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

void boss::startBoss(int WIDTH, int HEIGHT)
{
	live = true;
	x = (WIDTH/2) - frameWidth/2;
	y = -400;
}

void boss::updateBoss()
{
	collided = false;
	y += speed;
	if (y >= 100) {
		y = 100;
	}

	if (++frameCount > frameDelay) {
		frameCount = 0;
		if (++curFrame > 3)
			curFrame = 0;
	}

}
void boss::collideBoss(player& Player)
{
	if (live && !collided)
	{
		if (x - frameWidth / 2 < Player.getX() + Player.getWidth() / 2 &&
			x + frameWidth / 2 > Player.getX() - Player.getWidth() / 2 &&
			y - frameHeight / 2 < Player.getY() + Player.getHeight() / 2 &&
			y + frameHeight / 2 > Player.getY() - Player.getHeight() / 2)
		{
			Player.removeLife();
			collided = true;
		}
	}
}