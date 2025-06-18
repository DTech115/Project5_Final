//DT Nesimi

#include "player.h"
#include "enemy.h"

class bullet

{
public:
	bullet();
	~bullet();
	void drawBullet();
	void fireBullet(player& player);
	void updateBullet(int WIDTH, player& Player);
	void collideBullet (enemy enemy[], player& Player, int cSize);
private:
	int x;
	int y;
	bool live;
	int speed;
	float radian_angle = 0;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP* seal;
};