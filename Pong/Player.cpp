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
	unsigned int currentTime;

	//currentTime = SDL_GetTicks();

	// Change position every 5 miliseconds
	//if (lastTime + PLAYER_TAB_REFRESH_VALUE < currentTime)
	//{
		//lastTime = currentTime;

		// Manage separately for player one and two
	if (player == Player::ONE)
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
	//}


	if (PlayerCollision == true)
	{
		if (!Sprite::DrawAnimated(numberOfFrames, x, y, w, h))
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
}
