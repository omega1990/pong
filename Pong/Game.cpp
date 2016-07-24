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
static void matchFinished(Ball *ball, PowerupController *powerupController, SDL_Renderer *renderer);
static void controlPowerups(PowerupController *powerupController);
static void controlScore(Text *scoreText, Text *winningText, SDL_Renderer *renderer, Ball *ball, PowerupController* powerupController);
static void drawMainSprites(Background *background, Ball *ball, Player *playerOne, Player *playerTwo);
static void drawMenu(Background *background, Text *startNewGame, Text *exit);

static bool quit = false;


enum GamePhase
{
	MENU = 0,
	GAMEPLAY = 1
};

enum MenuItem
{
	START = 0, 
	EXIT  = 1
};

static MenuItem selectedMenuItem = START;

static GamePhase gamePhase = MENU;

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

		Background *background = new Background(renderer);
		Player *playerOne = new Player(renderer, Player::ONE, SpriteType::PLAYERONE);
		Player *playerTwo = new Player(renderer, Player::TWO, SpriteType::PLAYERTWO);
		Ball *ball = new Ball(renderer, 25, DEFAULT_BALL_SPEED, playerOne, playerTwo);
		Text *scoreText = new Text(renderer, Text::OUTLAW);
		Text *winningText = new Text(renderer, Text::DIESEL);
		Text *startNewGame = new Text(renderer, Text::DIESEL);
		startNewGame->Selected = true;
		Text *exit = new Text(renderer, Text::DIESEL);

		PowerupController *powerupController = new PowerupController(renderer, ball, playerOne, playerTwo);

		//While application is running
		while (!quit)
		{
			if (resetNeeded)
			{
				reset(&ball);
				powerupController->PowerupDeactivateAll();
			}

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
						if (downPressed)
						{
							selectedMenuItem = static_cast<MenuItem>((selectedMenuItem + 1) % 2);
						}
						downPressed = false;
					}
					if (e.key.keysym.sym == SDLK_UP)
					{
						if (upPressed)
						{
							selectedMenuItem = static_cast<MenuItem>(abs(((static_cast<int>(selectedMenuItem) - 1) % 2)));
						}
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
					if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
					{
						switch (selectedMenuItem)
						{
						case START:
							gamePhase = GAMEPLAY;
							break;
						case EXIT:
							close(&renderer, &window, &background, &ball, &playerOne, &playerTwo);
							return 0;
						default:
							// Do nothing
							break;
						}
					}
					break;
				}
				}
			}

			//Clear screen
			SDL_RenderClear(renderer);

			switch (gamePhase)
			{
			case MENU:
				switch (selectedMenuItem)
				{
				case START:
					startNewGame->SetSelected(true);
					exit->SetSelected(false);
					break;
				case EXIT:
					startNewGame->SetSelected(false);
					exit->SetSelected(true);
					break;
				default:
					break;
				}
				drawMenu(background, startNewGame, exit);
				break;
			case GAMEPLAY:
				drawMainSprites(background, ball, playerOne, playerTwo);
				controlScore(scoreText, winningText, renderer, ball, powerupController);
				controlPowerups(powerupController);
				break;
			default:
				break;
			}	

			//Update screen
			SDL_RenderPresent(renderer);	
			SDL_Delay(5);
		}

		close(&renderer, &window, &background, &ball, &playerOne, &playerTwo);

		return 0;
	}
}

static bool init(SDL_Window **window, SDL_Renderer **renderer)
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

static void close(SDL_Renderer **renderer, 
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

static void reset(Ball **ball)
{
	if(ball != NULL)
		(*ball)->ResetPosition();

	resetNeeded = false;
}

static void resetGame(Ball **ball)
{
	reset(ball);

	scorePlayerOne = 0;
	scorePlayerTwo = 0;
}

static void matchFinished(Ball *ball, PowerupController *powerupController, SDL_Renderer *renderer)
{
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	resetGame(&ball);
	powerupController->PowerupDeactivateAll();		
}

static void controlPowerups(PowerupController *powerupController)
{
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
}

static void controlScore(Text *scoreText, Text *winningText, SDL_Renderer *renderer, Ball *ball, PowerupController* powerupController)
{
    std::string scoreString = std::to_string(scorePlayerOne);
	const char* scoreChar = scoreString.c_str();

	scoreText->Write(scoreChar, SCORE_ONE_X, SCORE_Y);

	scoreString = std::to_string(scorePlayerTwo);
	scoreChar = scoreString.c_str();
	scoreText->Write(scoreChar, SCORE_TWO_X, SCORE_Y);

	if (scorePlayerOne == SCORE_FOR_VICTORY)
	{
		winningText->Write("Player One Wins!", 160, 65, 500);
		matchFinished(ball, powerupController, renderer);
	}
	else if (scorePlayerTwo == SCORE_FOR_VICTORY)
	{
		winningText->Write("Player Two Wins!", 160, 65, 500);
		matchFinished(ball, powerupController, renderer);
	}
}

static void drawMainSprites(Background *background, Ball *ball, Player *playerOne, Player *playerTwo)
{
	background->Draw(0, 0);
	ball->Draw();
	playerOne->Draw();
	playerTwo->Draw();
}

static void drawMenu(Background *background, Text *startNewGame, Text *exit)
{
	background->Draw(0, 0);
	startNewGame->WriteSelected("Start new game", (SCREEN_WIDTH-375)/2, 420, 375, 55);
	exit->WriteSelected("Exit", (SCREEN_WIDTH - 100) / 2, 485, 100, 55);
}