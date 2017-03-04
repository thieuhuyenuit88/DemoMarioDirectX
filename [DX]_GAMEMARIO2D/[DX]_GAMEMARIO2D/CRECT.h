#pragma once
class CRECT
{
public:
	float top, left, right, bottom;
	CRECT(void);
	//CRECT with right > left, top > bottom
	CRECT(float left, float right, float top, float bottom);
	~CRECT(void);

	bool isCollision (CRECT rect);
	bool isContain (CRECT rect);
};