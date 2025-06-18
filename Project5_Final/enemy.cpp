//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "enemy.h"
#include <iostream>

enemy::enemy()
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
	animationDirection = 2;

}
enemy::~enemy()
{
	al_destroy_bitmap(cirno);
	al_destroy_bitmap(cirno_dead);
}

void enemy::drawEnemy()
{
	if (live)
	{
		int fx = 0;
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
		if (++curFrame > 4)
			curFrame = 0;
	}

}
void enemy::collideEnemy(player& Player)
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
	if (y > 800)
	{
		live = false;
	}
}