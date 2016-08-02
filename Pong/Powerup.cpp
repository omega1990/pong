#include "Powerup.h"



Powerup::Powerup(SDL_Renderer *passedRenderer, SpriteType powerUpType, Ball *passedBall, Player *passedPlayerOne, Player *passedPlayerTwo, double passedX, double passedY) :
	Sprite(passedRenderer, powerUpType),
	Object(passedX, passedY, 72, 72),
	ball(passedBall),
	playerOne(passedPlayerOne),
	playerTwo(passedPlayerTwo)
{	
	
}

Powerup::~Powerup()
{
}




