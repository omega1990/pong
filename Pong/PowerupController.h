#pragma once
#include "Ball.h"
#include "Player.h"
#include "Powerup.h"

class PowerupController
{
public:

	enum PowerUp
	{
		GROW = 0
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

