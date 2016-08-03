#pragma once
#include "Sprite.h"
#include "Object.h"

class Explosion : public Sprite, public Object
{
public:
	Explosion(SDL_Renderer *passedRenderer);
	~Explosion();
	void DrawAnimated(double x, double y, bool *playExplosion);

private:
	unsigned int currentFrame = 0;
};

