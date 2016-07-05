#include "Fire.h"



Fire::Fire(SDL_Renderer *passedRenderer, double passedX, double passedY, SpriteType passedFireType):
	Sprite(passedRenderer, passedFireType),
	Object(0,0,0,0), 
	fireType(passedFireType)
{
	x = passedX;
	y = passedY;

	QueryDimensions(&w, &h, numberOfFrames);

}


Fire::~Fire()
{
}

void Fire::DrawAnimated(double y)
{
	if(fireType == SpriteType::FIREUP)
		Sprite::DrawAnimated(numberOfFrames, x, y - h, w, h);
	else
		Sprite::DrawAnimated(numberOfFrames, x, y, w, h);
}