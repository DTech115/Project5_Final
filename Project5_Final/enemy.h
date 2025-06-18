//DT Nesimi

#include "player.h"

class enemy
{
public:
    enemy();
    ~enemy();
    void drawEnemy();
    void startEnemy(int WIDTH, int HEIGHT);
    void updateEnemy();
    void collideEnemy(player& Player);
    int getBoundX() { return boundx; }
    int getBoundY() { return boundy; }
    int getX() { return x; }
    int getY() { return y; }
    bool getLive() { return live; }
    void setLive(bool l) { live = l; }

private:
    int x;
    int y;
    bool live;
    int speed;
    int boundx;
    int boundy;
    bool collided;
    ALLEGRO_BITMAP* cirno;
    ALLEGRO_BITMAP* cirno_dead;
};