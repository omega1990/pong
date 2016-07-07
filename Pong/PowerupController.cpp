#include "PowerupController.h"
#include "PowerupGrow.h"


typedef struct powerup
{
	Powerup *currentPowerup;
	unsigned int time;
	Player::playerNumber player;
	powerup *next;
} powerup;

static powerup *head;

void pushPowerup(Powerup *powerupToPush, Player::playerNumber player)
{
	if (head == nullptr)
	{
		head = new powerup;
		head->currentPowerup = powerupToPush;
		head->time = SDL_GetTicks();
		head->next = nullptr;
		head->player = player;
		return;
	}

	powerup *current = head;

	while (current->next != nullptr)
	{
		current = current->next;
	}
	current->next = new powerup;
	current->next->currentPowerup = powerupToPush;
	current->next->time = SDL_GetTicks();
	current->next->player = player;
	current->next->next = nullptr;	
}

void popPowerup()
{
	powerup *powerupToPop = head;
	head = head->next;
	free(powerupToPop);
	powerupToPop = nullptr;
}

static powerup powerups;

PowerupController::PowerupController(SDL_Renderer *passedRenderer, Ball *passedBall, Player *passedPlayerOne, Player *passedPlayerTwo):
	renderer(passedRenderer), 
	ball(passedBall),
	playerOne(passedPlayerOne), 
	playerTwo(passedPlayerTwo),
	powerUpOnField(false),
	currentPowerup(nullptr)
{
	head = nullptr;
}


PowerupController::~PowerupController()
{
}

bool PowerupController::IsTimeForPowerUp()
{
	if(SDL_GetTicks() % 501 == 0)
		return true;

	return false;
}

void PowerupController::SpawnPowerup()
{
	//if (currentPowerup)
	//	free(currentPowerup);

	x = rand() % ((SCREEN_WIDTH - TAB_DISTANCE - playerTwo->w - 100) - (TAB_DISTANCE + playerOne->w + 100) + 1) + (TAB_DISTANCE + playerOne->w + 100);
	y = rand() % ((SCREEN_HEIGHT - 100) - 99) + 99;

	currentPowerup = new PowerupGrow(renderer, ball, playerOne, playerTwo, x, y);	
	powerUpOnField = true;	

	powerups.currentPowerup = currentPowerup;
	powerups.next = nullptr;
}

void PowerupController::DrawPowerup()
{
	if (currentPowerup)
	{
		currentPowerup->Draw(x, y);
	}
}

void PowerupController::CheckCollision()
{
	if (ball->isInCollision((Object)*currentPowerup))
	{
		currentPowerup->ActivatePowerup();
		powerUpOnField = false;
		if (ball->directionHorizontal == Ball::direction::LEFT)
		{
			pushPowerup(currentPowerup, Player::playerNumber::TWO);
		}
		else if (ball->directionHorizontal == Ball::direction::RIGHT)
		{
			pushPowerup(currentPowerup, Player::playerNumber::ONE);
		}
	}
}

void PowerupController::TriggerDeactivation()
{
	powerup *current = head;

	while (current != nullptr)
	{
		if (current->time + 2000 < SDL_GetTicks())
		{
			current->currentPowerup->DeactivatePowerup(current->player);
			popPowerup();
			return;
		}
		current = current->next;
	}
}
