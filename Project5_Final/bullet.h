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
	void drawBossBullet();
	void fireBullet(player& player);
	void updateBullet(int WIDTH);

	void collideBullet (enemy enemy[], player& Player, int cSize);	//bullet collisions with enemies
	void collideBulletBoss(boss& boss);	//bullet collisions with boss

	void fireBossBullet(boss& boss);	//boss's bullet firing & updating
	void updateBossBullet(int WIDTH);

	void collidePlayerBullet(player& Player, int cSize);	//boss's bullet collisions with player
private:
	int x;
	int y;
	bool live;
	int speed;

	int orbFrame;

	ALLEGRO_BITMAP* seal;
	ALLEGRO_BITMAP* orb;
};