#pragma once
class Object
{
public:
	Object(int passedX, int passedY, int passedW, int passedH);
	~Object();
	double x;
	double y;
	int w;
	int h;
	bool isInCollision(Object object);
};

