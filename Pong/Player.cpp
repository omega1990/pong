#include "Player.h"

int tabWidth;
int tabHeight;
int playerOnePosition;
int playerTwoPosition;

Player::Player(SDL_Renderer *passedRenderer, playerNumber passedNumber, SpriteType passedSpriteType) :
	Sprite(passedRenderer, passedSpriteType),
	player(passedNumber),
	frameNumber(0),
	PlayerCollision(false)
{
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	tabWidth = static_cast<int>(width / numberOfFrames);
	tabHeight = height;
	positionY = (SCREEN_HEIGHT / 2) - (height / 2);

	if (player == ONE)
	{
		positionX = TAB_DISTANCE;
		playerOnePosition = positionY;
	}
	else
	{
		positionX = SCREEN_WIDTH - TAB_DISTANCE - tabWidth;
		playerTwoPosition = positionY;
	}

	lastTime = SDL_GetTicks();
	lastFrameTime = lastTime;
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

	if (PlayerCollision && lastFrameTime + 100 < currentTime)
	{
		frameNumber++;		
		lastFrameTime = currentTime;
	}

	if (frameNumber == numberOfFrames - 1)
	{
		frameNumber = 0;
		PlayerCollision = false;
	}

	Sprite::Draw(positionX, positionY, tabWidth-1, tabHeight, frameNumber*20, 0);
}
