#include "Text.h"



Text::Text(SDL_Renderer *passedRenderer, Font passedFont):
	renderer(passedRenderer),
	Selected(false),
	colorAdd(7),
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

void Text::WriteSelected(const char *text, int x, int y, int width, int height)
{	
	if (Selected)
	{
		color.r += colorAdd;
		color.g += colorAdd;
		color.b += colorAdd;
	
		if (color.r >= selHiglightLimit)
		{
			colorAdd = -colorAdd;
			color.r = selHiglightLimit - 1;
			color.g = selHiglightLimit - 1;
			color.b = selHiglightLimit - 1;
		}
		else if (color.r <= 0)
		{
			colorAdd = -colorAdd;
			color.r = 1;
			color.g = 1;
			color.b = 1;
		}
	}

	Write(text, x, y, width, height);
}

void Text::SetSelected(bool selected)
{
	Selected = selected;

	if (!selected)
	{
		resetColor();
	}
}

void Text::resetColor()
{
	color = { 0, 0, 0 };

}
