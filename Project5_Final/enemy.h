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

    ALLEGRO_BITMAP* cirno;
    ALLEGRO_BITMAP* cirno_dead;
};