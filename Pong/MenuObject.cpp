#include "MenuObject.h"



MenuObject::MenuObject(SDL_Renderer *passedRenderer, Font passedFont, int passedX, int passedY, int passedW, int passedH):
	Text(passedRenderer, passedFont, passedX, passedY, passedW, passedH),
	Arrow(passedRenderer, passedX - 50, passedY),
	Selected(false)
{
}


MenuObject::~MenuObject()
{
}

void MenuObject::SetSelected(bool selected)
{
	Selected = selected;

	if (!selected)
	{
		resetColor();
	}
}


void MenuObject::WriteSelected(const char *text)
{
	if (Selected)
	{
		Arrow::DrawAnimated();

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

	Write(text, Object::x, Object::y, Object::w, Object::h);	
}

