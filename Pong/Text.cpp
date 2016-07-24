#include "Text.h"



Text::Text(SDL_Renderer *passedRenderer, Font passedFont, int passedX, int passedY, int passedW, int passedH):
	Object(passedX, passedY, passedW, passedH),
	renderer(passedRenderer),
	colorAdd(5),
	selHiglightLimit(180)
{
	switch (passedFont)
	{
	case OUTLAW:
		font = TTF_OpenFont("Fonts/outlaw_regular.ttf", 275);
		break;
	case DIESEL:
		font = TTF_OpenFont("Fonts/DIESELPUNK.ttf", 275);
		break;
	default:
		// Do nothing 
		break;
	}

	resetColor();
}

Text::~Text()
{
	free(font);
	free(message);
}

void Text::Write(const char *text, int passedX, int passedY, int width, int height)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
	message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	if (passedX != -1 && passedY != -1)
	{
		messageRect.x = passedX;
		messageRect.y = passedY;
		messageRect.w = width;
		messageRect.h = height;
	}
	else
	{
		messageRect.x = x;
		messageRect.y = y;
		messageRect.w = w;
		messageRect.h = h;
	}

	SDL_FreeSurface(surfaceMessage);

	SDL_RenderCopy(renderer, message, NULL, &messageRect);
	SDL_DestroyTexture(message);
}

void Text::resetColor()
{
	color = { 0, 0, 0 };

}
