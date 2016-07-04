#include "Player.h"

int tabWidth;
int tabHeight;
int playerOnePosition;
int playerTwoPosition;

Player::Player(SDL_Renderer *passedRenderer,
	playerNumber passedNumber,
	SpriteType passedSpriteType) :
	Sprite(passedRenderer, passedSpriteType),
	Object(0, 0, 0, 0),
	player(passedNumber),
	frameNumber(0),
	PlayerCollision(false)
{
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	w = static_cast<int>(w / numberOfFrames);
	y = (SCREEN_HEIGHT / 2) - (h / 2);

	if (player == ONE)
	{
		x = PLAYER_ONE_POSITION_X;
		playerOnePosition = positionY;
	}
	else
	{
		x = PLAYER_TWO_POSITION_X - tabWidth;
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
	if (lastTime + PLAYER_TAB_REFRESH_VALUE < currentTime)
	{
		lastTime = currentTime;

		// Manage separately for player one and two
		if (player == Player::ONE)
		{
			if (wPressed && y > 0)
			{
				y -= TAB_SPEED;
			}
			else if (sPressed && y < SCREEN_HEIGHT - h)
			{
				y += TAB_SPEED;
			}
		}
		else
		{
			if (upPressed && y > 0)
			{
				y -= TAB_SPEED;
			}
			else if (downPressed && y < SCREEN_HEIGHT - h)
			{
				y += TAB_SPEED;
			}
		}
	}

	if (PlayerCollision && lastFrameTime + PLAYER_TAB_ANIMATION_REFRESH_VALUE < currentTime)
	{
		++frameNumber;
		lastFrameTime = currentTime;
	}

	if (frameNumber == numberOfFrames - 1)
	{
		frameNumber = 0;
		PlayerCollision = false;
	}

	Sprite::Draw(x, y, w - 1, h, frameNumber*w, 0);
}
