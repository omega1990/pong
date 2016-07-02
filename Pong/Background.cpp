#include "Background.h"
#include "SpritesEnum.h"



Background::Background(SDL_Renderer *passedRenderer):
	Sprite(passedRenderer, SpriteType::BACKGROUND)
{
}


Background::~Background()
{
}
