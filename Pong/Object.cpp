#include "Object.h"
#include <iostream>


Object::Object(int passedX, int passedY, int passedW, int passedH):
	x(passedX),
	y(passedY),
	w(passedW),
	h(passedH)
{
}


Object::~Object()
{
}


bool Object::isInCollision(Object object)
{
	if(x + w < object.x)
	{ 
		return false;
	}

	if (y + h < object.y)
	{
		return false;
	}

	if (y > object.y + object.h)
	{
		return false;
	}

	if (x > object.x + object.w)
	{
		return false;
	}

	return true;
}


