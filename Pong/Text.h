#pragma once
#include <SDL_ttf.h>

#include "Sprite.h"


class Text
{
public:
	enum Font
	{
		DIESEL=0, 
		OUTLAW=1
	};

	Text(SDL_Renderer *passedRenderer, Font passedFont);
	~Text();
	void Write(const char *text, int x, int y, int width = 50, int height = 100);
	void WriteSelected(const char *text, int x, int y, int width = 50, int height = 100);
	bool Selected;
	void SetSelected(bool selected);


private:
	TTF_Font *font;
	SDL_Renderer *renderer;
	SDL_Color color;
	SDL_Texture* message;
	std::string text;
	SDL_Rect messageRect;
	int colorAdd;
	void resetColor();
	const int selHiglightLimit;
};

