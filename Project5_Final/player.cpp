//DT Nesimi

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

player::~player()
{
	al_destroy_bitmap(reimu);
	al_destroy_bitmap(yinyang);
	al_destroy_bitmap(giantseal);
	al_destroy_bitmap(dead);

}
player::player()
{
	x = 355;
	y = 650;

	maxFrame = 24;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 64;
	frameHeight = 96;
	animationColumns = 8;
	animationDirection = 2;

	/*boundx = al_get_bitmap_width(reimu) * 0.2;
	boundy = al_get_bitmap_height(reimu) * 0.3;*/
	
	lives = 6;
	speed = 7;
	score = 0;

	reimu = al_load_bitmap("reimu_sheet.png");
	yinyang = al_load_bitmap("yinyang_sheet.png");
	giantseal = al_load_bitmap("seal_sheet.png");
	dead = al_load_bitmap("dead.png");
}

void player::DrawPlayer(int xoffset, int yoffset)
{

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = 0;

	
	if (animationDirection == 0) {//left
		fy = frameHeight;
	}
	else if (animationDirection == 1) {//right
		fy = 2 * frameHeight;
	}
	else { //idle/up/down
		fy = 0;
	}

	al_draw_bitmap_region(reimu, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);


	// other properties
	int lx = 0, ly = 0;
	int rx = 0, ry = 0;

	decorAngle += 0.2;

	if (lives >= 6) {
		lx = 0;
		ly = 0;
		rx = 0;
		ry = 0;
		/*al_draw_rotated_bitmap(yinyang, 32, 32, 500, 750, -decorAngle, 0);
		al_draw_bitmap(giantseal, x - 250, y, 0);
		al_draw_bitmap(giantseal, x + 270, y, 0);*/
	}
	else if (lives == 5) {
		lx = 0;
		ly = 32;
		rx = 0;
		ry = 64;
	}
	else if (lives == 4) {
		lx = 32;
		ly = 32;
		rx = 32;
		ry = 64;
	}
	else if (lives == 3) {
		lx = 64;
		ly = 32;
		rx = 64;
		ry = 64;
	}
	else if (lives == 2) {
		lx = 96;
		ly = 32;
		rx = 96;
		ry = 64;
	}
	else if (lives == 1) {
		lx = 128;
		ly = 32;
		rx = 128;
		ry = 64;
	}
	else {
		lx = 32;
		ly = 0;
		rx = 32;
		ry = 0;
	}
	ALLEGRO_BITMAP* frameL = al_create_sub_bitmap(yinyang, lx, ly, 32, 32);
	ALLEGRO_BITMAP* frameR = al_create_sub_bitmap(yinyang, rx, ry, 32, 32);
	al_draw_rotated_bitmap(frameL, 16, 16, x - 50, y + 50, decorAngle, 0);
	al_draw_rotated_bitmap(frameR, 16, 16, x + frameWidth + 40, y + 50, -decorAngle, 0);
	al_destroy_bitmap(frameL);
	al_destroy_bitmap(frameR);
}

void player::UpdateSprites(int width, int height, int dir) {

	if (dir == 0) { //left
		animationDirection = 0;
		x -= speed;
		if (x < 0) {
			x = 0;
		}
		if (curFrame < 7) {
			if (++frameCount > frameDelay) {
				frameCount = 0;
				curFrame++;
			}
		}
		else {
			curFrame == 8;
		}
	} else if (dir == 1) { //right
		animationDirection = 1;
		x += speed;
		if (x > width - frameWidth)
			x = width - frameWidth;

		if (curFrame < 7) {
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				curFrame++;
			}
		}
		else {
			curFrame == 8;
		}
	} else if (dir == 2) {//up
		animationDirection = 2;
		y -= speed;
		if (y < 0)
			y = 0;
		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > 8)
				curFrame = 1;
		}
	} else if (dir == 3) { // down
		animationDirection = 2;
		y += speed;
		if (y > height - frameHeight)
			y = height - frameHeight;
		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > 8)
				curFrame = 1;
		}
	}
	else {
		animationDirection = 2;
		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > 8)
				curFrame = 1;
		}
	}
}