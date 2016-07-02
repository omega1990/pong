#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Ball.h"
#include "Settings.h"
#include "GameState.h"

class Ball : public Sprite
{
public:
	enum direction
	{
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
		DOWN = 3
	};
	

	Ball(SDL_Renderer *passedRenderer, int passedSize, int passedSpeed);
	~Ball();
	void Draw();
	void ResetPosition();

	int positionX;
	int positionY;
	direction directionHorizontal;
	direction directionVertical;

private:
	SDL_Renderer *renderer;
	int size;
	int speed;		
};

