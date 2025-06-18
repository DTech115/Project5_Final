//DT Nesimi

#ifndef PLAYERH
#define PLAYERH
class player
{
public:

	player();
	~player();
	void DrawPlayer(int xoffset, int yoffset);
	void MoveUp(int width, int height, int dir);
	void MoveDown(int width, int height, int dir);
	void MoveLeft(int width, int height, int dir);
	void MoveRight(int width, int height, int dir);
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	int getX() { return x; }
	int getY() { return y; }
	void removeLife() { lives--; }

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
	/*ALLEGRO_BITMAP* yinyang;
	ALLEGRO_BITMAP* giantseal1;
	ALLEGRO_BITMAP* giantseal2;
	ALLEGRO_BITMAP* dead;*/

};
#endif
