#pragma once
#include "Sprite.h"
#include "Object.h"

class Fire : public Sprite, public Object 
{
public:
	Fire(SDL_Renderer *passedRenderer, double passedX, double passedY, SpriteType passedFireType);
	~Fire();

	void DrawAnimated(double y);

private:
	const int numberOfFrames = 5; 
	SpriteType fireType;

};

