//DT Nesimi
#ifndef BOSSH
#define BOSSH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "player.h"

class boss
{
public:
    // states for boss movement!!!
    enum BossState {
        DOWN, LEFT, PAUSELEFT, RIGHT, PAUSERIGHT
    };

    //similar to both player & enemy, poetic really
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
    int getLives() { return lives; }
    void removeLife() { lives--; }

private:
    int x;
    int y;
    bool alive;
    int lives;
    int speed;

    BossState state;    //to track said state
    int pauseTimer; //for how long boss should stop

    //animation stuff
    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationRows;

    ALLEGRO_BITMAP* remilia;
    ALLEGRO_BITMAP* remilia_dead;

    ALLEGRO_SAMPLE* hit;
};
#endif