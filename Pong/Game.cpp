#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <iostream>
#include <string>

#include "Settings.h"
#include "Background.h"
#include "Ball.h"
#include "Player.h"
#include "GameState.h"
#include "Text.h"
#include "PowerupController.h"

bool upPressed;
bool downPressed;
bool wPressed;
bool sPressed;
int scorePlayerOne;
int scorePlayerTwo;

//Starts up SDL and creates window
static bool init(SDL_Window **, SDL_Renderer **);

//Frees media and shuts down SDL
static void close(SDL_Renderer **renderer, 
	SDL_Window **window,
	Background**background, 
	Ball **ball, 
	Player **playerOne,
	Player **playerTwo);

static void reset(Ball **ball);
static void resetGame(Ball **ball);
static void matchFinished(Ball *ball, PowerupController *powerupController);

static bool quit = false;

int main(int argc, char *argv[])
{
	reset(NULL);

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The window renderer
	SDL_Renderer* renderer = NULL;

	//The thread for moving the ball
	SDL_Thread *handleBallThread = NULL;

	//Initialize SDL
	if (!init(&window, &renderer))
	{
		std::cout << "Failed to initialize!" << std::endl;
		return 0;
	}
	else
	{	
		SDL_Event e;

		// Variables for scoring player scores
		std::string scoreString;
		char const *scoreChar;

		Background *background = new Background(renderer);
		Player *playerOne = new Player(renderer, Player::ONE, SpriteType::PLAYERONE);
		Player *playerTwo = new Player(renderer, Player::TWO, SpriteType::PLAYERTWO);
		Ball *ball = new Ball(renderer, 25, DEFAULT_BALL_SPEED, playerOne, playerTwo);
		Text *text = new Text(renderer);
		PowerupController *powerupController = new PowerupController(renderer, ball, playerOne, playerTwo);

		//While application is running
		while (!quit)
		{
			if (resetNeeded) reset(&ball);

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
				case SDL_QUIT:
				{
					quit = true;
					break;
				}
				case SDL_KEYDOWN:
				{
					if (e.key.keysym.sym == SDLK_DOWN)
					{
						downPressed = true;
					}
					if (e.key.keysym.sym == SDLK_UP)
					{
						upPressed = true;
					}

					if (e.key.keysym.sym == SDLK_w)
					{
						wPressed = true;
					}
					if (e.key.keysym.sym == SDLK_s)
					{
						sPressed = true;
					}

					break;
				}
				case SDL_KEYUP:
				{
					if (e.key.keysym.sym == SDLK_DOWN)
					{
						downPressed = false;
					}
					if (e.key.keysym.sym == SDLK_UP)
					{
						upPressed = false;
					}
					if (e.key.keysym.sym == SDLK_w)
					{
						wPressed = false;
					}
					if (e.key.keysym.sym == SDLK_s)
					{
						sPressed = false;
					}
					break;
				}
				}
			}

			//Clear screen
			SDL_RenderClear(renderer);

			background->Draw(0, 0);
			ball->Draw();
			playerTwo->Draw();
			playerOne->Draw();

			scoreString = std::to_string(scorePlayerOne);
			scoreChar = scoreString.c_str();

			text->Write(scoreChar, SCORE_ONE_X, SCORE_Y);

			scoreString = std::to_string(scorePlayerTwo);
			scoreChar = scoreString.c_str();
			text->Write(scoreChar, SCORE_TWO_X, SCORE_Y);

			if (scorePlayerOne == SCORE_FOR_VICTORY)
			{
				text->Write("Player One Wins!", 150, 25, 500);				
				matchFinished(ball, powerupController);
			}
			else if (scorePlayerTwo == SCORE_FOR_VICTORY)
			{
				text->Write("Player Two Wins!", 150, 25, 500);				
				matchFinished(ball, powerupController);
			}

			if (powerupController->powerUpOnField == false && powerupController->IsTimeForPowerUp())
			{
				powerupController->PowerupSpawn();
			}

			if (powerupController->powerUpOnField)
			{
				powerupController->DrawPowerup();
				powerupController->CheckCollision();
			}

			powerupController->TriggerDeactivation();

			//Update screen
			SDL_RenderPresent(renderer);	

			SDL_Delay(5);
		}

		close(&renderer, &window, &background, &ball, &playerOne, &playerTwo);

		return 0;
	}
}

bool init(SDL_Window **window, SDL_Renderer **renderer)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		TTF_Init();
		//Create window
		*window = SDL_CreateWindow("Darko's Pong",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (*window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: %s "
				<< SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			//Create renderer for window
			*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0x00);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					return false;
				}
			}
		}
	}

	return true;
}

void close(SDL_Renderer **renderer, 
	SDL_Window **window, 
	Background **background, 
	Ball **ball, 
	Player **playerOne, 
	Player **playerTwo
	)
{
	//Destroy window    
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
	*window = NULL;
	*renderer = NULL;

	free(*playerTwo);
	free(*playerOne);
	free(*background);
	free(*ball);

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void reset(Ball **ball)
{
	if(ball != NULL)
		(*ball)->ResetPosition();

	resetNeeded = false;
}

void resetGame(Ball **ball)
{
	reset(ball);

	scorePlayerOne = 0;
	scorePlayerTwo = 0;
}

void matchFinished(Ball *ball, PowerupController *powerupController)
{
	SDL_Delay(2000);
	resetGame(&ball);
	powerupController->PowerupDeactivateAll();	
}