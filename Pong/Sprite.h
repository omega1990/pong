#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SpritesEnum.h"


class Sprite
{
public:
	Sprite(SDL_Renderer *passedRenderer, SpriteType passedSpriteType);
	~Sprite();	
	void Draw(double xPosition, double yPosition, int width = -1, int height = -1);

private:	
	SDL_Renderer *renderer;
	std::string path;
	SDL_Rect *rect;
	SDL_Rect *crop;
	void LoadTexture();

protected:
	SDL_Texture *texture;
};

