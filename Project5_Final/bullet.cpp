//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "bullet.h"
#include <iostream>

bullet::bullet()
{
	x = 400;
	y = 700;
	speed = 15;
	live = false;
	orbFrame = 0;
	seal = al_load_bitmap("seal.png");
	orb = al_load_bitmap("orb_sheet.png");

	hit = al_load_sample("hit.wav");
	shoot = al_load_sample("shoot.wav");
	remorb = al_load_sample("remorb.wav");
	cirnodead = al_load_sample("cirnodead.wav");
}
bullet::~bullet()
{
	al_destroy_bitmap(seal);
	al_destroy_bitmap(orb);

	al_destroy_sample(hit);
	al_destroy_sample(shoot);
	al_destroy_sample(remorb);
	al_destroy_sample(cirnodead);
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
		std::cout << "Firing sound: " << (shoot ? "VALID!" : "NULL!") << "\n";
		al_play_sample(shoot, 1.0, 0.0, 0.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
void bullet::drawBossBullet()
{
	if (live) {
		int fx = orbFrame * 64;
		int fy = 0;

		al_draw_bitmap_region(orb, fx, fy, 64, 64, x + 10, y, 0);
	}
}
void bullet::fireBossBullet(boss& Boss) {
	//shoots an orb of a random dimension from the sheet
	if (!live)
	{
		x = Boss.getX();
		y = Boss.getY();

		orbFrame = rand() % 4;
		live = true;
		al_play_sample(remorb, 1.0, 0.0, 0.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
	if (live && !Player.safe())
	{
		if (x > (Player.getX() - Player.getWidth() / 2) &&
			x < (Player.getX() + Player.getWidth() / 2) &&
			y >(Player.getY() - Player.getHeight() / 2) &&
			y < (Player.getY() + Player.getHeight() / 2))
		{
			live = false;
			Player.removeLife();
			Player.setiframes();
			Player.setiframeTimer();
			al_play_sample(hit, 1.0, 0.0, 0.0, ALLEGRO_PLAYMODE_ONCE, NULL);

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
					al_play_sample(cirnodead, 1.0, 0.0, 0.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
		}
	}

}