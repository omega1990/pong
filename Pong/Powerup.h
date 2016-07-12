#pragma once
#include "Sprite.h"
#include "Object.h"
#include "Ball.h"

class Powerup : public Sprite, public Object
{
public:
	Powerup(SDL_Renderer *passedRenderer, SpriteType powerUpType, Ball *passedBall, Player *passedPlayerOne, Player *passedPlayerTwo, double passedX, double passedY);
	~Powerup();
	virtual void ActivatePowerup() = 0;
	virtual void DeactivatePowerup() = 0;

	Player *player;


protected:
	Ball *ball;
	Player *playerOne;
	Player *playerTwo;
};

