//DT Nesimi

#include "player.h"

class boss
{
public:
    boss();
    ~boss();
    void drawBoss();
    void startBoss(int WIDTH, int HEIGHT);
    void updateBoss();
    void collideBoss(player& Player);
    int getWidth() { return frameWidth; }
    int getHeight() { return frameHeight; }
    int getX() { return x; }
    int getY() { return y; }
    bool getLive() { return live; }
    void setLive(bool l) { live = l; }

private:
    int x;
    int y;
    bool live;
    int speed;

    //animation stuff
    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationRows;


    bool collided;
    ALLEGRO_BITMAP* cirno;
    ALLEGRO_BITMAP* cirno_dead;
};