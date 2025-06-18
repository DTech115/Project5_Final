//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

player::~player()
{
	al_destroy_bitmap(reimu);
	/*al_destroy_bitmap(yinyang);
	al_destroy_bitmap(giantseal1);
	al_destroy_bitmap(giantseal2);
	al_destroy_bitmap(dead);*/

}
player::player()
{
	x = 355;
	y = 650;

	maxFrame = 24;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 96;
	frameHeight = 144;
	animationColumns = 8;
	animationDirection = 2;

	/*boundx = al_get_bitmap_width(reimu) * 0.2;
	boundy = al_get_bitmap_height(reimu) * 0.3;*/
	
	lives = 6;
	speed = 7;
	score = 0;

	reimu = al_load_bitmap("reimu_sheet.png");
	/*yinyang = al_load_bitmap("yinyang_sheet.png");
	giantseal1 = al_load_bitmap("seal_sheet.png");
	giantseal2 = al_load_bitmap("seal_sheet.png");
	dead = al_load_bitmap("dead.png");*/
}

void player::DrawPlayer(int xoffset, int yoffset)
{

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = 0;

	if (animationDirection == 2) {//idle
		fx = 0;
		fy = 0;
	}
	else if (animationDirection == 0) {//left
		fx = 0;
		fy = frameHeight;
	}
	else if (animationDirection == 1) {//right
		fx = 0;
		fy = 2 * frameHeight;
	}

	al_draw_bitmap_region(reimu, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);

	decorAngle += 0.2;
	//main sprite
	/*if (lives >= 6) {
		al_draw_bitmap(reimu, x, y, 0);
		al_draw_rotated_bitmap(yinyang, 32, 32, 300, 750, decorAngle, 0);
		al_draw_rotated_bitmap(yinyang, 32, 32, 500, 750, -decorAngle, 0);
		al_draw_bitmap(giantseal, x - 250, y, 0);
		al_draw_bitmap(giantseal, x + 270, y, 0);
	}
	else if (lives == 5) {
		al_draw_bitmap(reimu, x, y, 0);
		al_draw_rotated_bitmap(yinyangL1, 32, 32, 300, 750, decorAngle, 0);
		al_draw_rotated_bitmap(yinyangR1, 32, 32, 500, 750, -decorAngle, 0);
		al_draw_bitmap(giantsealL1, x - 250, y, 0);
		al_draw_bitmap(giantsealR1, x + 270, y, 0);
	}
	else if (lives == 4) {
		al_draw_bitmap(reimu, x, y, 0);
		al_draw_rotated_bitmap(yinyangL2, 32, 32, 300, 750, decorAngle, 0);
		al_draw_rotated_bitmap(yinyangR2, 32, 32, 500, 750, -decorAngle, 0);
		al_draw_bitmap(giantsealL2, x - 250, y, 0);
		al_draw_bitmap(giantsealR2, x + 270, y, 0);
	}
	else if (lives == 3) {
		al_draw_bitmap(reimu, x, y, 0);
		al_draw_rotated_bitmap(yinyangL3, 32, 32, 300, 750, decorAngle, 0);
		al_draw_rotated_bitmap(yinyangR3, 32, 32, 500, 750, -decorAngle, 0);
		al_draw_bitmap(giantsealL3, x - 250, y, 0);
		al_draw_bitmap(giantsealR3, x + 270, y, 0);
	}
	else if (lives == 2) {
		al_draw_bitmap(reimu, x, y, 0);
		al_draw_rotated_bitmap(yinyangL4, 32, 32, 300, 750, decorAngle, 0);
		al_draw_rotated_bitmap(yinyangR4, 32, 32, 500, 750, -decorAngle, 0);
		al_draw_bitmap(giantsealR4, x + 270, y, 0);
	}
	else if (lives == 1) {
		al_draw_bitmap(reimu, x, y, 0);
		al_draw_rotated_bitmap(yinyangL5, 32, 32, 300, 750, decorAngle, 0);
		al_draw_rotated_bitmap(yinyangR5, 32, 32, 500, 750, -decorAngle, 0);
	}
	else {
		al_draw_bitmap(power, 400, 760, 0);
		al_draw_bitmap(power, 365, 750, 0);
		al_draw_bitmap(power, 420, 690, 0);
		al_draw_bitmap(power, 435, 730, 0);
		al_draw_bitmap(power, 385, 754, 0);
		al_draw_bitmap(power, 390, 710, 0);

	}*/
}

//converted to radians
void player::MoveLeft(int width, int height, int dir)
{

	x -= speed;
	if (x < 0)
		x = 0;
}
void player::MoveRight(int width, int height, int dir)
{
	x += speed;
	if (x > width - frameWidth)
		x = width - frameWidth;
}
void player::MoveUp(int width, int height, int dir) {
	y -= speed;
	if (y < 400)
		y = 400;
}
void player::MoveDown(int width, int height, int dir) {
	y += speed;
	if (y > height - frameHeight)
		y = height - frameHeight;
}