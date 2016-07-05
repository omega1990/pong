#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Settings.h"
#include "GameState.h"
#include "Object.h"
#include "Fire.h"

class Player : public Sprite, public Object
{
public:
	enum playerNumber
	{
		ONE = 1,
		TWO = 2
	};

	Player(SDL_Renderer *passedRenderer, playerNumber player, SpriteType passedSpriteType);
	~Player();
	void Draw();

	bool PlayerCollision;

private:
	int height;
	int width;
	int positionY;
	int positionX; 
	playerNumber player;
	unsigned int lastTime;
	unsigned int lastFrameTime;
	int frameNumber;
	const int numberOfFrames = 5;
	Fire *fireUp;
	Fire *fireDown;

	void setCoordinates();
};

