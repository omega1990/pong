#include "Sprite.h"

Sprite::Sprite(SDL_Renderer *passedRenderer, SpriteType spriteType) :
	renderer(passedRenderer),
	frameNumber(0),
	lastFrameTime(0)
{
	ChangeTexture(spriteType);
	
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
	
	if (texture != nullptr)
		SDL_DestroyTexture(texture);

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

void Sprite::QueryDimensions(int *width, int *height, int numberOfFrames) const
{
	SDL_QueryTexture(texture, NULL, NULL, width, height);
	*width /= numberOfFrames;	
}


bool Sprite::DrawAnimated(const int numberOfFrames, 
	const double xPosition, 
	double yPosition, 
	int width, 
	int height, 
	const int animationPeriod)
{		
	if (width == -1 && height == -1)
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	currentTime = SDL_GetTicks();

	Draw(xPosition, yPosition, width/numberOfFrames, height, frameNumber*(width/numberOfFrames), 0);
	
	if (lastFrameTime + animationPeriod < currentTime)
	{
		lastFrameTime = currentTime;
		if (frameNumber == numberOfFrames - 1)
		{
			frameNumber = 0;
			return false;
		}		
		frameNumber++;
	}	

	return true;
}


void Sprite::ChangeTexture(SpriteType spriteType)
{
	std::string newPath;
	
	switch (spriteType)
	{
	case BACKGROUND:
		newPath = "Textures/PongBackground.png";
		break;
	case BALL:
		newPath = "Textures/BallAnimated.png";
		break;
	case PLAYERONE:
		newPath = "Textures/TabOneAnimated.png";
		break;
	case PLAYERTWO:
		newPath = "Textures/TabTwoAnimated.png";
		break;
	case FIREDOWN:
		newPath = "Textures/FireDownAnimated.png";
		break;
	case FIREUP:
		newPath = "Textures/FireUpAnimated.png";
		break;
	case POWERUP_GROW:
		newPath = "Textures/PU_Grow.png";
		break;
	case PLAYERONEGROW:
		newPath = "Textures/OneAnimatedGrow.png";
		break;
	case PLAYERTWOGROW:
		newPath = "Textures/TwoAnimatedGrow.png";
		break;
	case BALL_SPEED:
		newPath = "Textures/BallAnimated.png";
		break;
	case POWERUP_BALL_SPEED:
		newPath = "Textures/PU_BallSpeed.png";
		break;
	case ARROW:
		newPath = "Textures/Arrow.png";
		break;
	case STARSHINE:
		newPath = "Textures/StarShine.png";
		break;
	case STARSHINESMALL:
		newPath = "Textures/StarShineSmall.png";
		break;
	case EXPLOSION:
		newPath = "Textures/explosion.png";
		break;
	default:
		break;
	}

	if (path.compare(newPath) != 0)
	{
		path = newPath;
		LoadTexture();
	}
}

