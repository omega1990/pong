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
	void Draw(double xPosition, double yPosition, int width = -1, int height = -1, int offsetX = 0, int offsetY = 0);
	bool DrawAnimated(const int numberOfFrames, 
		const double xPosition, 
		const double yPosition, 
		const int width = -1,
		const int height = -1, 
		const int animationPeriod = 100);
	void QueryDimensions(int *width, int *height, int numberOfFrames) const;

private:	
	SDL_Renderer *renderer;
	std::string path;
	SDL_Rect *rect;
	SDL_Rect *crop;
	void LoadTexture();
	int frameNumber;
	unsigned int lastFrameTime;
	unsigned int currentTime;


protected:
	SDL_Texture *texture;
};

