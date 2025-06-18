//DT Nesimi

#ifndef PLAYERH
#define PLAYERH
class player
{
public:

	player();
	~player();
	void DrawPlayer(int xoffset, int yoffset);
	void UpdateSprites(int width, int height, int dir); //dir 1 = right, 0 = left, 2 = up/down/idle
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	int getX() { return x; }
	int getY() { return y; }
	void removeLife() { lives--; }
	void resetFrame() { curFrame = 0; }

	int getLives() { return lives; }	// returns lives for lives check
	void increaseScore() { score++; }	//increases score :]
	int getScore() { return score; }	//returns score!
private:
	int x;
	int y;
	int lives;
	int speed;
	int score;

	//animation stuff
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int animationDirection;

	float decorAngle = 0;

	ALLEGRO_BITMAP* reimu;
	ALLEGRO_BITMAP* yinyangl;
	ALLEGRO_BITMAP* yinyangr;
	/*ALLEGRO_BITMAP* giantseall;
	ALLEGRO_BITMAP* giantsealr;
	ALLEGRO_BITMAP* dead;*/

};
#endif
