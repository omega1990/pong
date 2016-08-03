#include "StarShine.h"


StarShine::StarShine(SDL_Renderer *passedRenderer, SpriteType passedType) :
	Sprite(passedRenderer, passedType),
	Object(0, 0, 0, 0)
{
	QueryDimensions(&w, &h, numberOfFrames);
}

void StarShine::DrawAnimated(double x, double y)
{	
	int randAnimPeriod = rand() % (200 - 50 + 1) + 50;
	Sprite::DrawAnimated(numberOfFrames, x, y, -1, -1, randAnimPeriod);
}

StarShine::~StarShine()
{
}
