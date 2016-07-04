#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Ball.h"
#include "Settings.h"
#include "GameState.h"
#include "Player.h"

class Ball : public Sprite, public Object
{
public:
	enum direction
	{
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
		DOWN = 3
	};
	

	Ball(SDL_Renderer *passedRenderer, int passedSize, int passedSpeed, Player *passedPlayerOne, Player *passedPlayerTwo);
	~Ball();
	void Draw();
	void ResetPosition();
		
	direction directionHorizontal;
	direction directionVertical;

private:
	void handleCollision();
	SDL_Renderer *renderer;	
	int speed;		
	double xSpeedComponent;
	double ySpeedComponent;
	Player *playerOne; 
	Player *playerTwo;

	unsigned int lastTime;
};

