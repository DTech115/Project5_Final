//DT Nesimi

#include "player.h"
#include "enemy.h"
#include "boss.h"

class bullet

{
public:
	bullet();
	~bullet();
	void drawBullet();
	void fireBullet(player& player);
	void updateBullet(int WIDTH);
	void collideBullet (enemy enemy[], player& Player, int cSize);
	void collideBulletBoss(boss& boss);

	void fireBossBullet(boss& boss);
	void updateBossBullet(int WIDTH);
	void collidePlayerBullet(player& Player, int cSize);
private:
	int x;
	int y;
	bool live;
	int speed;
	float angle = 0;
	int boundx;
	int boundy;

	ALLEGRO_BITMAP* seal;
};