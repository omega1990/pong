#include "Arrow.h"



Arrow::Arrow(SDL_Renderer *passedRenderer, double passedX, double passedY):
	Sprite(passedRenderer, ARROW),
	Object(passedX, passedY, 0, 0)
{
	QueryDimensions(&w, &h, numberOfFrames);
}


Arrow::~Arrow()
{
}


void Arrow::DrawAnimated()
{	
	Sprite::DrawAnimated(numberOfFrames, x, y);	
}