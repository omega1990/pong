#include "PowerupController.h"



typedef struct powerup
{
	Powerup *currentPowerup;
	unsigned int time;
	powerup *next;
} powerup;

static powerup *head;

void pushPowerup(Powerup *powerupToPush, Player *player)
{
	if (head == nullptr)
	{
		std::cout << "Creating new" << std::endl;

		head = new powerup;
		head->currentPowerup = powerupToPush;
		head->time = SDL_GetTicks();
		head->next = nullptr;
		head->currentPowerup->player = player;
		return;
	}

	powerup *current = head;
	

	// Loop until the last FIFO buffer element
	while (current->next != nullptr)
	{
		std::cout << player->PlayerNumber << "==" << current->currentPowerup->player->PlayerNumber << std::endl;

		// If player collected the same power-up, just extend the power-up duration
		if ((typeid(*(current->currentPowerup)).name() == typeid(*powerupToPush).name()) &&
			(player == current->currentPowerup->player))
		{
			std::cout << "Extending!" << std::endl;
			current->time = SDL_GetTicks();
			// There is no need to add more power-ups because existing one has been extended
			return;
		}

		current = current->next;
	}

	// If there is only one power-up in FIFO buffer
	if (current->next == nullptr)
	{
		std::cout << player->PlayerNumber << "==" << current->currentPowerup->player->PlayerNumber << std::endl;

		// If player collected the same power-up, just extend the power-up duration
		if ((typeid(*(current->currentPowerup)).name() == typeid(*powerupToPush).name()) &&
			(player == current->currentPowerup->player))
		{
			std::cout << "Extending!" << std::endl;
			current->time = SDL_GetTicks();
			// There is no need to add more power-ups because existing one has been extended
			return;
		}
	}

	std::cout << "Creating new" << std::endl;
	current->next = new powerup;
	current->next->currentPowerup = powerupToPush;
	current->next->currentPowerup->player = player;
	current->next->time = SDL_GetTicks();
	current->next->next = nullptr;
}

void popPowerup(powerup *powerupToPop)
{
	// Nothing to pop
	if (!head)
	{
		return;
	}

	// There is only power-up in buffer
	if (head->next == nullptr)
	{
		head = nullptr;
		delete head;
		return;
	}

	powerup *current = head;
	powerup *previous = nullptr;

	while (current)
	{
		if ((typeid(*(current->currentPowerup)).name() == typeid(*(powerupToPop->currentPowerup)).name()) &&
			(powerupToPop->currentPowerup->player == current->currentPowerup->player))
		{
			if (!previous)
			{
				powerup *powerUpToDelete = head;
				head = head->next;
				powerUpToDelete = nullptr;
				delete powerUpToDelete;
				return;
			}
			else
			{
				previous = current->next;
				current = nullptr;
				delete current;
				return;
			}
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

void PowerupController::SpawnPowerup()
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
