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

	bool safe() { return iframes; };	//gives back if the player is invincible
	void setiframes() { iframes = true; }	//sets player to invincible
	void setiframeTimer() { iframeTimer = 60; } //timer for how long player is invincible, 1 second
private:
	int x;
	int y;
	int lives;
	int speed;
	int score;
	bool iframes;	//for not getting hit too fast
	int iframeTimer;

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

	float angle = 0;

	ALLEGRO_BITMAP* reimu;
	ALLEGRO_BITMAP* yinyang;
	ALLEGRO_BITMAP* giantseal;
	ALLEGRO_BITMAP* dead;

};
#endif
