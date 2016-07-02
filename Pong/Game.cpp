#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Settings.h"
#include "Background.h"
#include "Ball.h"
#include "Player.h"
#include "GameState.h"

bool upPressed;
bool downPressed;
bool wPressed;
bool sPressed;

//Starts up SDL and creates window
bool init(SDL_Window **, SDL_Renderer **);

//Frees media and shuts down SDL
void close(SDL_Renderer **renderer, 
	SDL_Window **window,
	Background**background, 
	Ball **ball, 
	Player **playerOne);

void reset(Ball **ball);

int main(int argc, char *argv[])
{
	reset(NULL);

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The window renderer
	SDL_Renderer* renderer = NULL;

	//Initialize SDL
	if (!init(&window, &renderer))
	{
		std::cout << "Failed to initialize!" << std::endl;
		return 0;
	}
	else
	{
		bool quit = false;
		SDL_Event e;

		Background *background = new Background(renderer);
		Ball *ball = new Ball(renderer, 25, 3);
		Player *playerOne = new Player(renderer, Player::ONE);
		Player *playerTwo = new Player(renderer, Player::TWO);

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

			//Update screen
			SDL_RenderPresent(renderer);
		}

		close(&renderer, &window, &background, &ball, &playerTwo);

		return 0;
	}
}

bool init(SDL_Window **window, SDL_Renderer **renderer)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		//Create window
		*window = SDL_CreateWindow("SDL Tutorial",
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
	Player **playerOne)
{
	//Destroy window    
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
	*window = NULL;
	*renderer = NULL;

	free(*playerOne);
	free(*background);
	free(*ball);

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void reset(Ball **ball)
{
	upPressed = false;
	downPressed = false;
	wPressed = false;
	sPressed = false;

	if(ball != NULL)
		(*ball)->ResetPosition();

	resetNeeded = false;
}