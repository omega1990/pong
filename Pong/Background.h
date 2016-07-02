#pragma once
#include "Sprite.h"

class Background : public Sprite
{
public:
	Background(SDL_Renderer *passedRenderer);
	~Background();
};

