//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "bullet.h"
#include <math.h>
#include <iostream>

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

void bullet::updateBullet(int WIDTH)
{
	if (live)
	{
		y -= speed;

		if (y < 0)
			live = false;
	}
}

void bullet::fireBossBullet(boss& Boss) {
	
	if (!live)
	{
		x = Boss.getX();
		y = Boss.getY();

		live = true;
	}

}
void bullet::updateBossBullet(int WIDTH) {
	if (live) {
		y += speed;

		if (y > 800) {
			live = false;
		}
	}
}
void bullet::collidePlayerBullet(player& Player, int cSize) {
	if (live)
	{
		if (x > (Player.getX() - Player.getWidth() / 2) &&
			x < (Player.getX() + Player.getWidth() / 2) &&
			y >(Player.getY() - Player.getHeight() / 2) &&
			y < (Player.getY() + Player.getHeight() / 2))
		{
			live = false;
			Player.removeLife();
			std::cout << "HP: " << Player.getLives() << "\n";
		}
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
				if (x > (enemy[j].getX() - enemy[j].getWidth() / 2) &&
					x < (enemy[j].getX() + enemy[j].getWidth() / 2) &&
					y >(enemy[j].getY() - enemy[j].getHeight() / 2) &&
					y < (enemy[j].getY() + enemy[j].getHeight() / 2))
				{
					live = false;
					enemy[j].setLive(false);
					Player.increaseScore();				// increases score upon hit!!!
				}
			}
		}
	}

}
void bullet::collideBulletBoss(boss& boss)
{
	if (live)
	{
		
		if (x > (boss.getX() - boss.getWidth() / 2) &&
			x < (boss.getX() + boss.getWidth() / 2) &&
			y >(boss.getY() - boss.getHeight() / 2) &&
			y < (boss.getY() + boss.getHeight() / 2))
		{
			live = false;
			boss.removeLife();
			std::cout << "HP: " << boss.getLives() << "\n";
		}
	}

}