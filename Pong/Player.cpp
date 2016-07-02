#include "Player.h"

int tabWidth;
int tabHeight;
int playerOnePosition;
int playerTwoPosition;

Player::Player(SDL_Renderer *passedRenderer, playerNumber passedNumber) :
	Sprite(passedRenderer, SpriteType::PLAYER),
	player(passedNumber)
{
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	tabWidth = width;
	tabHeight = height;
	positionY = (SCREEN_HEIGHT / 2) - (height / 2);

	if (player == ONE)
	{
		positionX = TAB_DISTANCE;
		playerOnePosition = positionY;
	}
	else
	{
		positionX = SCREEN_WIDTH - TAB_DISTANCE;
		playerTwoPosition = positionY;
	}

	lastTime = SDL_GetTicks();
}


Player::~Player()
{
}

void Player::Draw()
{
	unsigned int currentTime;

	currentTime = SDL_GetTicks();

	// Change position every 5 miliseconds
	if (lastTime + 5 < currentTime)
	{
		lastTime = currentTime;

		// Manage separately for player one and two
		if (player == Player::ONE)
		{
			if (wPressed && positionY > 0)
			{
				positionY-=TAB_SPEED;
			}
			else if (sPressed && positionY < SCREEN_HEIGHT-height)
			{
				positionY+=TAB_SPEED;
			}
			playerOnePosition = positionY;
		}
		else
		{
			if (upPressed && positionY > 0)
			{
				positionY -= TAB_SPEED;
			}
			else if (downPressed && positionY < SCREEN_HEIGHT - height)
			{
				positionY += TAB_SPEED;
			}
			playerTwoPosition = positionY;
		}

	}

	Sprite::Draw(positionX, positionY);
}
