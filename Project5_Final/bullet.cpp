//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "bullet.h"
#include <math.h>

bullet::bullet()
{
	x = 400;
	y = 700;
	speed = 15;
	live = false;
	seal = al_load_bitmap("seal.png");
	boundx = al_get_bitmap_width(seal);
	boundy = al_get_bitmap_height(seal);
}
bullet::~bullet()
{
	al_destroy_bitmap(seal);
}
void bullet::drawBullet()
{
	if (live) {
		al_draw_bitmap(seal, x+20, y-50, 0);
	}
}
void bullet::fireBullet(player& Player)
{
	if (!live)
	{
		x = Player.getX();
		y = Player.getY();

		live = true;
	}
}

void bullet::updateBullet(int WIDTH, player& Player)
{
	if (live)
	{
		y -= speed;

		if (y < 0)
			live = false;
	}
}
void bullet::collideBullet(enemy enemy[], player& Player, int cSize)
{
	if (live)
	{
		for (int j = 0; j < cSize; j++)
		{
			if (enemy[j].getLive())
			{
				if (x > (enemy[j].getX() - enemy[j].getBoundX()) &&
					x < (enemy[j].getX() + enemy[j].getBoundX()) &&
					y >(enemy[j].getY() - enemy[j].getBoundY()) &&
					y < (enemy[j].getY() + enemy[j].getBoundY()))
				{
					live = false;
					enemy[j].setLive(false);
					Player.increaseScore();				// increases score upon hit!!!
				}
			}
		}
	}

}