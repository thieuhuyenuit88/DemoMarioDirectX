#include "CRECT.h"
#include <math.h>


CRECT::CRECT(void)
{
	left = right = top = bottom = 0;
}
CRECT::CRECT(float left, float right, float top, float bottom)
{
	this->left	= left;
	this->right	= right;
	this->top		= top;
	this->bottom	= bottom;
}

CRECT::~CRECT(void)
{
}

bool CRECT::isCollision(CRECT rect)
{
	float dh = (fabs(top-rect.bottom)>fabs((bottom-rect.top))) ? fabs(top-rect.bottom) : fabs((bottom-rect.top));
	float dw = (fabs(left - rect.right) > fabs(right - rect.left)) ? fabs(left-rect.right) : fabs(right - rect.left);

	return ((dw <= ((right-left)+(rect.right-rect.left)))&&
		(dh <= ((top - bottom) + (rect.top - rect.bottom))));
}

bool CRECT::isContain(CRECT rect)
{
	return (rect.left >= left)
		&&(rect.right <= right)
		&&(rect.top <= top)
		&&(rect.bottom >= bottom);
}