#include "Ball.h"

bool resetNeeded = false;

Ball::Ball(SDL_Renderer *passedRenderer, int passedSize, int passedSpeed, Player *passedPlayerOne, Player *passedPlayerTwo) :
	Sprite(passedRenderer, SpriteType::BALL),
	size(passedSize),
	speed(passedSpeed),
	positionX((SCREEN_WIDTH / 2) - (passedSize / 2)),
	positionY((SCREEN_HEIGHT / 2) - (passedSize / 2)),
	directionHorizontal(RIGHT),
	directionVertical(DOWN),
	lastTime(SDL_GetTicks()),
	xSpeedComponent(passedSpeed / 2),
	ySpeedComponent(passedSpeed / 2),
	playerOne(passedPlayerOne),
	playerTwo(passedPlayerTwo)
{
}


Ball::~Ball()
{
}


void Ball::Draw()
{
	handleCollision();
	Sprite::Draw(positionX, positionY, size, size);
}


void Ball::ResetPosition()
{
	positionX = (SCREEN_WIDTH / 2) - (size / 2);
	positionY = (SCREEN_HEIGHT / 2) - (size / 2);
	xSpeedComponent = speed / 2;
	ySpeedComponent = speed / 2;
}

void Ball::handleCollision()
{
	unsigned int currentTime;

	currentTime = SDL_GetTicks();

	if (lastTime + 5 < currentTime)
	{
		lastTime = currentTime;

		// Hit player two
		if (positionX >= (SCREEN_WIDTH - TAB_DISTANCE - tabWidth - size) &&
			positionY > playerTwoPosition &&
			positionY < (playerTwoPosition + tabHeight) &&
			positionX + size < (SCREEN_WIDTH - TAB_DISTANCE + tabWidth)
			)
		{
			playerTwo->PlayerCollision = true;
			directionHorizontal = LEFT;

			double placeOfImpact = (positionY - playerTwoPosition) / tabHeight;

			if (placeOfImpact == 0.0)
			{
				if (directionVertical == DOWN) directionVertical = UP;
				else directionVertical = DOWN;
			}
			else
			{
				if (directionVertical == DOWN)
				{
					if (placeOfImpact <= 0.5)
					{
						directionVertical = UP;
					}
				}
				else if (directionVertical == UP)
				{
					if (placeOfImpact >= 0.5)
					{
						directionVertical = DOWN;
					}
				}

				ySpeedComponent = abs(speed * (1 - 2 * placeOfImpact)) * 0.6;
				xSpeedComponent = speed - ySpeedComponent;
			}

		}
		// Hit player one
		else if (positionX <= (TAB_DISTANCE + tabWidth) &&
			positionY > playerOnePosition &&
			positionY < (playerOnePosition + tabHeight) &&
			positionX >(TAB_DISTANCE))
		{
			playerOne->PlayerCollision = true;

			directionHorizontal = RIGHT;

			double placeOfImpact = (positionY - playerOnePosition) / tabHeight;

			if (placeOfImpact == 0.0)
			{
				if (directionVertical == DOWN) directionVertical = UP;
				else directionVertical = DOWN;
			}
			else
			{
				if (directionVertical == DOWN)
				{
					if (placeOfImpact <= 0.5)
					{
						directionVertical = UP;
					}
				}
				else if (directionVertical == UP)
				{
					if (placeOfImpact >= 0.5)
					{
						directionVertical = DOWN;
					}
				}

				ySpeedComponent = abs(speed * (1 - 2 * placeOfImpact)) * 0.6;
				xSpeedComponent = speed - ySpeedComponent;
			}
		}
		else
		{
			// Manage direction change
			if (positionX > SCREEN_WIDTH - size)
			{
				directionHorizontal = LEFT;
				scorePlayerOne++;
				resetNeeded = true;
			}
			else if (positionX < 0)
			{
				directionHorizontal = RIGHT;
				scorePlayerTwo++;
				resetNeeded = true;
			}

			if (positionY > SCREEN_HEIGHT - size)
			{
				directionVertical = UP;
			}
			else if (positionY < 0)
			{
				directionVertical = DOWN;
			}
		}

		switch (directionHorizontal)
		{
		case RIGHT:
			positionX += xSpeedComponent;
			break;
		case LEFT:
			positionX -= xSpeedComponent;
			break;
		}

		switch (directionVertical)
		{
		case DOWN:
			positionY += ySpeedComponent;
			break;
		case UP:
			positionY -= ySpeedComponent;
			break;
		default:
			break;
		}

	}
}