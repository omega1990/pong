#include "Ball.h"

bool resetNeeded = false;

Ball::Ball(SDL_Renderer *passedRenderer, int passedSize, int passedSpeed, Player *passedPlayerOne, Player *passedPlayerTwo) :
	Sprite(passedRenderer, SpriteType::BALL),
	Object(static_cast<int>((SCREEN_WIDTH / 2) - (passedSize / 2)), 
			static_cast<int>((SCREEN_HEIGHT / 2) - (passedSize / 2)), 
			passedSize, 
			passedSize),
	speed(passedSpeed),
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
	Sprite::Draw(x, y, w, h);
}


void Ball::ResetPosition()
{
	x = (SCREEN_WIDTH / 2) - (w / 2);
	y = (SCREEN_HEIGHT / 2) - (h / 2);
	xSpeedComponent = speed / 2;
	ySpeedComponent = speed / 2;
}

void Ball::handleCollision()
{
		// Hit player two
		if(isInCollision(static_cast<Object>(*playerTwo)))
		{
			playerTwo->PlayerCollision = true;
			directionHorizontal = LEFT;

			double placeOfImpact = (y - playerTwo->y) / playerTwo->h;

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
		if (isInCollision(static_cast<Object>(*playerOne)))
		{
			playerOne->PlayerCollision = true;

			directionHorizontal = RIGHT;

			double placeOfImpact = (y - playerOne->y) / playerOne->h;

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
			if (x > SCREEN_WIDTH - w)
			{
				directionHorizontal = LEFT;
				scorePlayerOne++;
				resetNeeded = true;
			}
			else if (x < 0)
			{
				directionHorizontal = RIGHT;
				scorePlayerTwo++;
				resetNeeded = true;
			}

			if (y > SCREEN_HEIGHT - h)
			{
				directionVertical = UP;
			}
			else if (y < 0)
			{
				directionVertical = DOWN;
			}
		}

		switch (directionHorizontal)
		{
		case RIGHT:
			x += xSpeedComponent;
			break;
		case LEFT:
			x -= xSpeedComponent;
			break;
		}

		switch (directionVertical)
		{
		case DOWN:
			y += ySpeedComponent;
			break;
		case UP:
			y -= ySpeedComponent;
			break;
		default:
			break;
		}
}


void Ball::ChangeSpeed(double amount)
{
	ySpeedComponent /= speed;
	ySpeedComponent *= amount;

	speed = static_cast<int>(amount);
	xSpeedComponent = speed - ySpeedComponent;
}
