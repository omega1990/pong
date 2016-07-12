#pragma once
#include "Powerup.h"
#include "Ball.h"

class PowerupGrow : public Powerup
{
public:
	PowerupGrow(SDL_Renderer *passedRenderer, Ball *passedBall, Player *passedPlayerOne, Player *passedPlayerTwo, double passedX, double passedY);
	~PowerupGrow();

	virtual void ActivatePowerup() override;
	virtual void DeactivatePowerup() override;

};

