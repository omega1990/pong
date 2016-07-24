#pragma once
#include "Sprite.h"
#include "Object.h"

class Arrow : public Sprite, public Object
{
public:
	Arrow(SDL_Renderer *passedRenderer, double passedX, double passedY);
	~Arrow();
	void DrawAnimated();

private:
	const int numberOfFrames = 5;
};

