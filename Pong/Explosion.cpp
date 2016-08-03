#include "Explosion.h"



Explosion::Explosion(SDL_Renderer *passedRenderer) :
	Sprite(passedRenderer, SpriteType::EXPLOSION),
	Object(0, 0, 0, 0)
{
}


Explosion::~Explosion()
{
}


void Explosion::DrawAnimated(double x, double y, bool *playExplosion)
{	
	Sprite::DrawAnimated(16, x, y);
	currentFrame++;

	if (currentFrame == 16)
	{
		*playExplosion = false;
		currentFrame = 0;
	}
}