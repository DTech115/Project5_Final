//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "enemy.h"
#include <iostream>

enemy::enemy()
{
	cirno = al_load_bitmap("cirno.png");
	cirno_dead = al_load_bitmap("cirno_dead.png");
	live = false;
	collided = false;
	speed = 5;
	boundx = al_get_bitmap_width(cirno) * .5;
	boundy = al_get_bitmap_height(cirno) * .5;
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
		al_draw_bitmap(cirno, x, y, 0);
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
			x = rand() % (WIDTH - boundx);
			y = -100;

		}
		/*else {
			std::cout << "Fail :[ ";
		}*/

	}
}

void enemy::updateEnemy()
{

	y += speed;


}
void enemy::collideEnemy(player& Player)
{
	if (live && !collided)
	{
		if (x - boundx < Player.getX() + Player.getWidth() &&
			x + boundx > Player.getX() - Player.getWidth() &&
			y - boundy < Player.getY() + Player.getHeight() &&
			y + boundy > Player.getY() - Player.getHeight())
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