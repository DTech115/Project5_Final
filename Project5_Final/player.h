//DT Nesimi

#ifndef PLAYERH
#define PLAYERH
class player
{
public:

	player();
	~player();
	void DrawPlayer();
	void MoveUp();
	void MoveDown(int HEIGHT);
	void MoveLeft();
	void MoveRight(int WIDTH);
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
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
	int boundx;
	int boundy;
	int score;
	float decorAngle = 0;

	ALLEGRO_BITMAP* reimu;
	ALLEGRO_BITMAP* yinyang;

	ALLEGRO_BITMAP* yinyangL1;
	ALLEGRO_BITMAP* yinyangL2;
	ALLEGRO_BITMAP* yinyangL3;
	ALLEGRO_BITMAP* yinyangL4;
	ALLEGRO_BITMAP* yinyangL5;
	ALLEGRO_BITMAP* yinyangR1;
	ALLEGRO_BITMAP* yinyangR2;
	ALLEGRO_BITMAP* yinyangR3;
	ALLEGRO_BITMAP* yinyangR4;
	ALLEGRO_BITMAP* yinyangR5;

	ALLEGRO_BITMAP* giantseal;
	ALLEGRO_BITMAP* giantsealL1;
	ALLEGRO_BITMAP* giantsealL2;
	ALLEGRO_BITMAP* giantsealL3;
	ALLEGRO_BITMAP* giantsealR1;
	ALLEGRO_BITMAP* giantsealR2;
	ALLEGRO_BITMAP* giantsealR3;
	ALLEGRO_BITMAP* giantsealR4;

	ALLEGRO_BITMAP* power;

};
#endif
