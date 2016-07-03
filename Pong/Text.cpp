#include "Text.h"



Text::Text(SDL_Renderer *passedRenderer):
	renderer(passedRenderer)
{
	font = TTF_OpenFont("Fonts/outlaw_regular.ttf", 272);
	//color = { 247, 227, 165};
	color = { 0, 0, 0 };
}

Text::~Text()
{
	free(font);
	free(message);
}

void Text::Write(const char *text, int x, int y, int width, int height)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
	message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	messageRect.x = x;
	messageRect.y = y;
	messageRect.w = width;
	messageRect.h = height;

	SDL_FreeSurface(surfaceMessage);

	SDL_RenderCopy(renderer, message, NULL, &messageRect);
	SDL_DestroyTexture(message);
}