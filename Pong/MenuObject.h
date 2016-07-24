#pragma once
#include "Text.h"
#include "Arrow.h"

class MenuObject : public Text, public Arrow
{
public:
	MenuObject(SDL_Renderer *passedRenderer, Font passedFont, int passedX, int passedY, int passedW, int passedH);
	~MenuObject();
	bool Selected;
	void SetSelected(bool selected);
	void MenuObject::WriteSelected(const char *text);
};

