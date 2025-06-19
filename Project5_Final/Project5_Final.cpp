//DT Nesimi
#include <iostream>

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "player.h"
#include "bullet.h"
#include "boss.h"

//moving background method!
void scrollBackground();

//background global vars & dimensions
ALLEGRO_BITMAP* bg = NULL;
ALLEGRO_BITMAP* moon = NULL;
float bg_y1 = 0;
float bg_y2 = 0;
float scroll_speed = 2.0;
//float moonAngle = 0.0;

const int WIDTH = 800;
const int HEIGHT = 800;

int main()
{
    
    const int numBullets = 40;
    const int enemiesStage1 = 10;
    const int enemiesStage2 = 20;
    enum KEYS { LEFT, RIGHT, UP, DOWN, SPACE };
    bool keys[5] = { false, false, false, false, false };

    //primitive variable
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
    bool gameOver = false; //	gameover check for drawing gameover text
    bool stageOneOver = false, stageTwoOver = false; //  //makes sure you only pass the stage once
    int stage = 1;  //  which stage it is

    //Allegro variables
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;

    //Initialization Functions
    if (!al_init())										//initialize Allegro
        return -1;

    display = al_create_display(WIDTH, HEIGHT);			//create our display object

    if (!display)										//test display object
        return -1;

    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    al_init_primitives_addon();


    ALLEGRO_FONT* gameoverFont = al_load_font("DFPPOPCorn-W12.ttf", 64, 0);		//gameover font
    ALLEGRO_FONT* mainFont = al_load_font("DFPPOPCorn-W12.ttf", 32, 0);		//font

    //object variables
    player myPlayer;
    bullet bullets[numBullets];
    enemy enemies[enemiesStage1];   //different enemy types
    enemy enemies2[enemiesStage2];
    boss bigboss;   // boss
    bullet bossBullets[numBullets]; //boss fires back

    int xOff = 0;
    int yOff = 0;

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    srand(time(NULL));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);

    bg = al_load_bitmap("background.png");
    moon = al_load_bitmap("moon.png");

    bg_y1 = 0;
    bg_y2 = -al_get_bitmap_height(bg);


    //game loop
    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {

            if (myPlayer.getScore() >= 3 && !stageOneOver) {
                stage++;
                std::cout << "Stage " << stage << std::endl;
                stageOneOver = true;
            }
            if (myPlayer.getScore() >= 6 && !stageTwoOver) {
                stage++;
                std::cout << "Stage " << stage << std::endl;
                stageTwoOver = true;
            }

            redraw = true;

            bool idle = true;   //checks if not moving

            if (keys[LEFT]) {
                idle = false;
                myPlayer.UpdateSprites(WIDTH, HEIGHT, 0);
            }
            if (keys[RIGHT]) {
                idle = false;
                myPlayer.UpdateSprites(WIDTH, HEIGHT, 1);
            }
            if (keys[UP]) {
                idle = false;
                myPlayer.UpdateSprites(WIDTH, HEIGHT, 2);
            }
            if (keys[DOWN]) {
                idle = false;
                myPlayer.UpdateSprites(WIDTH, HEIGHT, 3);
            }
            if (idle) {
                myPlayer.UpdateSprites(WIDTH, HEIGHT, 4);
            }   //if not moving, player still animates

            // spawns the proper enemies depending on stage!
            if (stage == 1) {
                for (int i = 0; i < numBullets; i++)
                    bullets[i].updateBullet(WIDTH);
                for (int i = 0; i < enemiesStage1; i++)
                    enemies[i].startEnemy(WIDTH, HEIGHT);
                for (int i = 0; i < enemiesStage1; i++)
                    enemies[i].updateEnemy();
                for (int i = 0; i < numBullets; i++) {
                    bullets[i].collideBullet(enemies, myPlayer, numBullets);
                }
                for (int i = 0; i < enemiesStage1; i++)
                    enemies[i].collideEnemy(myPlayer);
            }
            else if (stage == 2) {
                for (int i = 0; i < numBullets; i++)
                    bullets[i].updateBullet(WIDTH);
                for (int i = 0; i < enemiesStage2; i++)
                    enemies2[i].startEnemy(WIDTH, HEIGHT);
                for (int i = 0; i < enemiesStage2; i++)
                    enemies2[i].updateEnemy();
                for (int i = 0; i < numBullets; i++) {
                    bullets[i].collideBullet(enemies2, myPlayer, numBullets);
                }
                for (int i = 0; i < enemiesStage2; i++)
                    enemies2[i].collideEnemy(myPlayer);
            }
            else if (stage == 3) {
                for (int i = 0; i < numBullets; i++)
                    bullets[i].updateBullet(WIDTH);
                bigboss.startBoss(WIDTH, HEIGHT);
                bigboss.updateBoss();
                for (int i = 0; i < numBullets; i++) {
                    bullets[i].collideBulletBoss(bigboss);
                }
                bigboss.collideBoss(myPlayer);
                
                for (int i = 0; i < numBullets; i++) {
                    bossBullets[i].collidePlayerBullet(myPlayer, numBullets);
                }
                if (bigboss.getLives() <= 0) {
                    gameOver = true;
                }
            }
            for (int i = 0; i < numBullets; i++)
                bossBullets[i].fireBossBullet(bigboss);

            if (myPlayer.getLives() <= 0) {
                gameOver = true;
            }
            
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                for (int i = 0; i < numBullets; i++)
                    bullets[i].fireBullet(myPlayer);
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            //background draw
            scrollBackground();
            al_draw_bitmap(moon, 140, 40, 0);

            myPlayer.DrawPlayer(xOff, yOff);
            for (int i = 0; i < numBullets; i++) {
                bullets[i].drawBullet();
            }

            if (stage == 1) {
                for (int i = 0; i < enemiesStage1; i++) {
                    enemies[i].drawEnemy();
                }
            }
            else if (stage == 2) {
                for (int i = 0; i < enemiesStage2; i++) {
                    enemies2[i].drawEnemy();
                }
            }
            else if (stage == 3) {
                bigboss.drawBoss();
                for (int i = 0; i < numBullets; i++) {
                    bossBullets[i].drawBullet();
                }
            }

            if (gameOver) {	
                al_draw_text(gameoverFont, al_map_rgb(0, 0, 200), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "GAME OVER!");
                al_draw_textf(mainFont, al_map_rgb(255, 255, 255), WIDTH / 2, (HEIGHT / 2) + 100, ALLEGRO_ALIGN_CENTER, "FAIRIES DEFEATED: %i", myPlayer.getScore());
                al_flip_display();
                al_rest(5);
                done = true;
            }
            al_draw_textf(mainFont, al_map_rgb(255, 200, 255), 0, 0, 0, "STAGE %i", stage);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }

    al_destroy_bitmap(bg);
    al_destroy_bitmap(moon);
    al_destroy_font(gameoverFont);
    al_destroy_font(mainFont);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);						//destroy our display object
    system("Pause");
    return 0;
}


// method for moving background down the screen
void scrollBackground() {
    // move both backgrounds down
    bg_y1 += scroll_speed;
    bg_y2 += scroll_speed;
    //moonAngle += 0.007;

    // reset if they're off screen
    if (bg_y1 >= HEIGHT)
        bg_y1 = bg_y2 - al_get_bitmap_height(bg);
    if (bg_y2 >= HEIGHT)
        bg_y2 = bg_y1 - al_get_bitmap_height(bg);

    al_draw_bitmap(bg, 0, bg_y1, 0);
    al_draw_bitmap(bg, 0, bg_y2, 0);
    //al_draw_rotated_bitmap(moon, al_get_bitmap_width(moon) / 2.0, al_get_bitmap_width(moon) / 2.0, 400, 300, moonAngle, 0);

}