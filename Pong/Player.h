#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Settings.h"
#include "GameState.h"

class Player : public Sprite
{
public:
	enum playerNumber
	{
		ONE = 1,
		TWO = 2
	};

	Player(SDL_Renderer *passedRenderer, playerNumber player);
	~Player();
	void Draw();

private:
	int height;
	int width;
	int positionY;
	int positionX; 
	playerNumber player;
	unsigned int lastTime;
};

