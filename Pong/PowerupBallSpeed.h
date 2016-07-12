#pragma once
#include "Powerup.h"


class PowerupBallSpeed : public Powerup
{
public:
	PowerupBallSpeed(SDL_Renderer *passedRenderer, Ball *passedBall, Player *passedPlayerOne, Player *passdPlayerTwo, double passedX, double passedY);
	~PowerupBallSpeed();
	
	virtual void ActivatePowerup() override;
	virtual void DeactivatePowerup() override;
};


