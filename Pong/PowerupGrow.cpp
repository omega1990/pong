#include "PowerupGrow.h"



PowerupGrow::PowerupGrow(SDL_Renderer *passedRenderer, Ball *passedBall, Player *passedPlayerOne, Player *passedPlayerTwo, double passedX, double passedY):
	Powerup(passedRenderer, SpriteType::POWERUP_GROW, passedBall, passedPlayerOne, passedPlayerTwo, passedX, passedY)
{
}


PowerupGrow::~PowerupGrow()
{
}

void PowerupGrow::ActivatePowerup()
{
	Player *activatingPlayer = nullptr;
	SpriteType sprite;
	int oldHeight, newHeight = 0;


	if (ball->directionHorizontal == Ball::LEFT)
	{
		activatingPlayer = playerTwo; 
		sprite = SpriteType::PLAYERTWOGROW;
	}
	else
	{
		activatingPlayer = playerOne;
		sprite = SpriteType::PLAYERONEGROW;
	}

	activatingPlayer->ChangeTexture(sprite);
	oldHeight = activatingPlayer->h;
	activatingPlayer->ResetDimensions();
	newHeight = activatingPlayer->h;

	activatingPlayer->y -= (newHeight - oldHeight) / 2;

	if (activatingPlayer->y + activatingPlayer->h >= SCREEN_HEIGHT)
	{
		activatingPlayer->y -= (activatingPlayer->y + activatingPlayer->h) - SCREEN_HEIGHT;
	}
	else if (activatingPlayer->y + activatingPlayer->h < 0)
	{
		activatingPlayer->y = 0;
	}
}

void PowerupGrow::DeactivatePowerup()
{	
	if (player->PlayerNumber == Player::playerNumber::ONE)
	{
		player->ChangeTexture(SpriteType::PLAYERONE);
		
	}
	else if (player->PlayerNumber == Player::playerNumber::TWO)
	{
		player->ChangeTexture(SpriteType::PLAYERTWO);
	}

	int oldHeight = player->h;
	player->ResetDimensions();
	int newHeight = player->h;

	player->y += (oldHeight - newHeight) / 2;
}


