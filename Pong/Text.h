#pragma once
#include <SDL_ttf.h>

#include "Sprite.h"
#include "Object.h"


class Text : public Object
{
public:
	enum Font
	{
		DIESEL=0, 
		OUTLAW=1, 
		JEDI=2, 
		SPACE=3
	};

	Text(SDL_Renderer *passedRenderer, Font passedFont, int passedX = -1, int passedY = -1, int passedW = 50, int passedH = 100);
	~Text();
	void Write(const char *text, int x = -1, int y = -1, int width = 50, int height = 100);
	
	
private:
	TTF_Font *font;
	SDL_Renderer *renderer;
	SDL_Texture* message;
	std::string text;
	SDL_Rect messageRect;

protected:
	void resetColor();
	const int selHiglightLimit;
	SDL_Color color;
	int colorAdd;

};

