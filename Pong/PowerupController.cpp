#include "PowerupController.h"



typedef struct powerup
{
	Powerup *currentPowerup;
	unsigned int time;
	powerup *next;
} powerup;

static powerup *head;

powerup* createPowerup(Powerup *powerupToPush, Player *player)
{
	powerup *createdPowerup = new powerup;
	createdPowerup->currentPowerup = powerupToPush;
	createdPowerup->time = SDL_GetTicks();
	createdPowerup->next = nullptr;
	createdPowerup->currentPowerup->player = player;
	return createdPowerup;
}

void pushPowerup(Powerup *powerupToPush, Player *player)
{
	if (head == nullptr)
	{
		head = createPowerup(powerupToPush, player);
		return;
	}

	powerup *current = head;

	while (current)
	{
		if ((typeid(*(current->currentPowerup)).name() == typeid(*powerupToPush).name()) &&
			(player == current->currentPowerup->player))
		{
			break;
		}

		current = current->next;
	}

	current = createPowerup(powerupToPush, player);
}

void popPowerup(powerup *powerupToPop)
{
	// Nothing to pop
	if (!head)
	{
		return;
	}

	powerup *previous = nullptr;
	powerup *current = head;

	while (current)
	{
		if ((typeid(*(current->currentPowerup)).name() == typeid(*(powerupToPop->currentPowerup)).name()) &&
			(powerupToPop->currentPowerup->player == current->currentPowerup->player))
		{
			if (previous)
			{
				previous->next = current->next;
			}

			if (current == head)
			{
				head = head->next;
			}

			current = nullptr;
			delete current;
			return;
		}

		previous = current;
		current = current->next;
	}

}

void destroyPowerups()
{
	powerup *current = head;

	while (current)
	{
		powerup *powerUpToDestroy = current;
		current = current->next;
		powerUpToDestroy->currentPowerup->DeactivatePowerup();
		powerUpToDestroy = nullptr;
		delete powerUpToDestroy;
	}
}

static powerup powerups;

PowerupController::PowerupController(SDL_Renderer *passedRenderer, Ball *passedBall, Player *passedPlayerOne, Player *passedPlayerTwo) :
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
	destroyPowerups();
}

bool PowerupController::IsTimeForPowerUp()
{
	if (SDL_GetTicks() % POWERUP_FREQUENCY == 0)
		return true;

	return false;
}

void PowerupController::PowerupSpawn()
{
	x = rand() % ((SCREEN_WIDTH - TAB_DISTANCE - playerTwo->w - 100) - (TAB_DISTANCE + playerOne->w + 100) + 1) + (TAB_DISTANCE + playerOne->w + 100);
	y = rand() % ((SCREEN_HEIGHT - 100) - 99) + 99;

	int powerUp = rand() % 2 + 0;

	switch (static_cast<PowerUp>(powerUp))
	{
	case GROW:
		currentPowerup = new PowerupGrow(renderer, ball, playerOne, playerTwo, x, y);
		break;
	case BALL_SPEED:
		currentPowerup = new PowerupBallSpeed(renderer, ball, playerOne, playerTwo, x, y);
		break;
	default:
		return;
	}

	powerUpOnField = true;
}

void PowerupController::DrawPowerup()
{
	if (currentPowerup)
	{
		currentPowerup->DrawAnimated(5, x, y);
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
			pushPowerup(currentPowerup, playerTwo);
		}
		else if (ball->directionHorizontal == Ball::direction::RIGHT)
		{
			pushPowerup(currentPowerup, playerOne);
		}
	}
}

void PowerupController::TriggerDeactivation()
{
	powerup *current = head;

	while (current != nullptr)
	{
		if ((current->time + POWERUP_DURATION) < SDL_GetTicks())
		{
			current->currentPowerup->DeactivatePowerup();
			popPowerup(current);
			return;
		}
		current = current->next;
	}
}

void PowerupController::PowerupDeactivateAll()
{
	destroyPowerups();
}
