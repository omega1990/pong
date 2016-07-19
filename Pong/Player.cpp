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
	PlayerNumber(passedNumber),
	frameNumber(0),
	PlayerCollision(false)
{
	QueryDimensions(&w, &h, numberOfFrames);
	setCoordinates();

	lastTime = SDL_GetTicks();
	lastFrameTime = lastTime;

	fireUp = new Fire(passedRenderer, x, y, SpriteType::FIREUP);
	fireDown = new Fire(passedRenderer, x, y + h, SpriteType::FIREDOWN);
}


Player::~Player()
{
	free(fireDown);
	free(fireUp);
}

void Player::Draw()
{
	// Manage separately for player one and two
	if (PlayerNumber == Player::ONE)
	{
		if (wPressed && y > 0)
		{
			y -= TAB_SPEED;
			fireDown->DrawAnimated(y + h);			
		}
		else if (sPressed && y < SCREEN_HEIGHT - h)
		{
			y += TAB_SPEED;
			fireUp->DrawAnimated(y);
		}
	}
	else
	{
		if (upPressed && y > 0)
		{
			y -= TAB_SPEED;
			fireDown->DrawAnimated(y+h);
		}
		else if (downPressed && y < SCREEN_HEIGHT - h)
		{
			y += TAB_SPEED;
			fireUp->DrawAnimated(y);
		}
	}


	if (PlayerCollision == true)
	{
		if (!Sprite::DrawAnimated(numberOfFrames, x, y))
			PlayerCollision = false;
	}
	else
	{
		Sprite::Draw(x, y, w, h);
	}
}


void Player::setCoordinates()
{
	y = (SCREEN_HEIGHT / 2) - (h / 2);

	if (PlayerNumber == ONE)
	{
		x = PLAYER_ONE_POSITION_X;
		playerOnePosition = positionY;
	}
	else
	{
		x = PLAYER_TWO_POSITION_X - tabWidth;
		playerTwoPosition = positionY;
	}
}

void Player::ResetDimensions()
{
	QueryDimensions(&w, &h, numberOfFrames);
}
