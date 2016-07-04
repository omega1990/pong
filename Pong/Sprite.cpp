#include "Sprite.h"

Sprite::Sprite(SDL_Renderer *passedRenderer, SpriteType spriteType):
	renderer(passedRenderer)
{
	switch (spriteType)
	{
	case BACKGROUND:
		path = "Textures/PongBackground.png";
		break;
	case BALL:
		path = "Textures/Ball.png";
		break;
	case PLAYERONE:
		path = "Textures/TabOneAnimated.png";
		break;
	case PLAYERTWO:
		path = "Textures/TabTwoAnimated.png";
		break;
	default:
		break;
	}
	
	rect = new SDL_Rect();
	crop = new SDL_Rect();

	LoadTexture();
}

Sprite::~Sprite()
{
	free(rect);
	free(crop);
	SDL_DestroyTexture(texture);
}

void Sprite::LoadTexture()
{
	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
}

void Sprite::Draw(double xPosition, double yPosition, int width, int height, int offsetX, int offsetY)
{
	// If width and height are not send to Draw function, use defaults
	if(width == -1 && height == -1)
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	rect->x = static_cast<int>(xPosition);
	rect->y = static_cast<int>(yPosition);
	rect->w = static_cast<int>(width);
	rect->h = static_cast<int>(height);

	crop->x = offsetX;
	crop->y = offsetY;
	crop->w = width;
	crop->h = height;
	
	// Render texture to screen
	SDL_RenderCopy(renderer, texture, crop, rect);
}


