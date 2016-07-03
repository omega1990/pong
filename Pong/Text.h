#pragma once
#include <SDL_ttf.h>

#include "Sprite.h"


class Text
{
public:
	Text(SDL_Renderer *passedRenderer);
	~Text();
	void Write(const char *text, int x, int y, int width = 50, int height = 100);

private:
	TTF_Font *font;
	SDL_Renderer *renderer;
	SDL_Color color;
	SDL_Texture* message;
	std::string text;
	SDL_Rect messageRect;
};

