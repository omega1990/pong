#pragma once
#include "Sprite.h"
#include "Object.h"

class StarShine: public Sprite, public Object
{
public:
	StarShine(SDL_Renderer *passedRenderer, double passedX, double passedY, SpriteType passedFireType);
	~StarShine();

	void DrawAnimated(double x, double y);
	void DrawAnimatedSmall(double x, double y);


private:
	const int numberOfFrames = 5;
};

