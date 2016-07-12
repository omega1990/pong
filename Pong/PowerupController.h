#pragma once
#include "Ball.h"
#include "Player.h"
#include "Powerup.h"
#include "PowerupGrow.h"
#include "PowerupBallSpeed.h"
#include "Settings.h"

class PowerupController
{
public:

	enum PowerUp
	{
		GROW = 0,
		BALL_SPEED = 1
	};

	PowerupController(SDL_Renderer *passedRenderer, Ball *passedBall, Player *passedPlayerOne, Player *passedPlayerTwo);
	~PowerupController();
	void SpawnPowerup();
	bool IsTimeForPowerUp();
	Powerup *currentPowerup;
	void CheckCollision();
	void DrawPowerup();
	void TriggerDeactivation();
	bool powerUpOnField;
	unsigned int powerupTimer;

	double x;
	double y;

private:
	SDL_Renderer *renderer;
	Ball *ball;
	Player *playerOne;
	Player *playerTwo;
};

