#pragma once
#include "Ball.h"
#include "Player.h"
#include "Powerup.h"
#include "PowerupGrow.h"
#include "PowerupBallSpeed.h"
#include "Settings.h"
#include "Explosion.h"

typedef struct powerup
{
	Powerup *currentPowerup;
	unsigned int time;
	powerup *next;
} powerup;

class PowerupController
{
public:
	bool powerUpOnField;
	enum PowerUp
	{
		GROW = 0,
		BALL_SPEED = 1
	};
	
	PowerupController(SDL_Renderer *passedRenderer, 
		Ball *passedBall, 
		Player *passedPlayerOne, 
		Player *passedPlayerTwo);
	~PowerupController();
	void PowerupSpawn();
	void PowerupDeactivateAll();
	bool IsTimeForPowerUp();
	bool CheckCollision();
	void DrawPowerup();
	void TriggerDeactivation();

	void GetPowerupCoordinates(double *x, double *y);

private:
	Powerup *currentPowerup;
	SDL_Renderer *renderer;
	Ball *ball;
	Player *playerOne;
	Player *playerTwo;
	powerup *head;
	double x;
	double y;

	powerup* powerupCreate(Powerup *powerupToPush, Player *player);
	void powerupPush(Powerup *powerupToPush, Player *player);
	void powerupPop(powerup *powerupToPop);
	void powerupDestroyAll();
};

