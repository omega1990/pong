#pragma once
#include "Sprite.h"
#include "Object.h"

class StarShine: public Sprite, public Object
{
public:
	StarShine(SDL_Renderer *passedRenderer, SpriteType passedFireType);
	~StarShine();

	void DrawAnimated(double x, double y);

private:
	const int numberOfFrames = 5;
};

