#include "PowerupBallSpeed.h"



PowerupBallSpeed::PowerupBallSpeed(SDL_Renderer *passedRenderer, Ball *passedBall, Player *passedPlayerOne, Player *passedPlayerTwo, double passedX, double passedY):
	Powerup(passedRenderer, SpriteType::POWERUP_BALL_SPEED, passedBall, passedPlayerOne, passedPlayerTwo, passedX, passedY)
{
}


PowerupBallSpeed::~PowerupBallSpeed()
{
}


void PowerupBallSpeed::ActivatePowerup()
{
	ball->ChangeSpeed(HIGH_BALL_SPEED);	
	ball->ChangeTexture(BALL_SPEED);
}

void PowerupBallSpeed::DeactivatePowerup()
{
	ball->ChangeSpeed(DEFAULT_BALL_SPEED);
	ball->ChangeTexture(BALL);
}




