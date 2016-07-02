#include "Ball.h"

bool resetNeeded = false;

Ball::Ball(SDL_Renderer *passedRenderer, int passedSize, int passedSpeed) :
	Sprite(passedRenderer, SpriteType::BALL),
	size(passedSize),
	speed(passedSpeed),
	positionX((SCREEN_WIDTH / 2) - (passedSize / 2)),
	positionY((SCREEN_HEIGHT / 2) - (passedSize / 2)),
	directionHorizontal(RIGHT),
	directionVertical(DOWN)
{
}


Ball::~Ball()
{
}


void Ball::Draw()
{
	static unsigned int lastTime = SDL_GetTicks(), currentTime;

	currentTime = SDL_GetTicks();

	if (lastTime + 5 < currentTime)
	{
		lastTime = currentTime;

		if (positionX > (SCREEN_WIDTH - TAB_DISTANCE - tabWidth - size) &&
			positionY > playerTwoPosition &&
			positionY < (playerTwoPosition + tabHeight) &&
			positionX < (SCREEN_WIDTH - TAB_DISTANCE))
		{
			directionHorizontal = LEFT;
		}
		else if (positionX < (TAB_DISTANCE + tabWidth + 5) &&
			positionY > playerOnePosition &&
			positionY < (playerOnePosition + tabHeight))
		{
			directionHorizontal = RIGHT;
		}
		else
		{
			// Manage direction change
			if (positionX > SCREEN_WIDTH - size)
			{
				directionHorizontal = LEFT;
				resetNeeded = true;
			}
			else if (positionX < 0)
			{
				directionHorizontal = RIGHT;
				resetNeeded = true;
			}

			if (positionY > SCREEN_HEIGHT - size)
			{
				directionVertical = DOWN;
			}
			else if (positionY < 0)
			{
				directionVertical = UP;
			}
		}

		switch (directionHorizontal)
		{
		case RIGHT:
			positionX += speed;
			break;
		case LEFT:
			positionX -= speed;
			break;
		}

		switch (directionVertical)
		{
		case UP:
			positionY += speed;
			break;
		case DOWN:
			positionY -= speed;
			break;
		default:
			break;
		}

	}

	Sprite::Draw(positionX, positionY, size, size);
}


void Ball::ResetPosition()
{
	positionX = (SCREEN_WIDTH / 2) - (size / 2);
	positionY = (SCREEN_HEIGHT / 2) - (size / 2);
}
