#include "MyObject.h"
#include <math.h>

MyObject::MyObject(void){
	oID = 0;
	oDirect = 0;
	oSTT = 0;
	oOldSTT = 0;
	oPosX = 0;
	oPosY = 0;
	oVx = 0;
	oVy = 0;
	oAccelX = 0;
	oAccelY = 0;
	oGravity = 0;
	sizeHeight = sizeWidth = 0;
	timeUpdate = timeAnimate = deltaTimeUpdate = 0;
}

MyObject::~MyObject(void){}

MyObject::MyObject(MyObject *obj){
	oID = obj->getID();
	oDirect = obj->getDirect();
	oSTT = obj->getSTT();
	oOldSTT = obj->getOldSTT();
	oPosX = obj->getPosX();
	oPosY = obj->getPosY();
	oVx = obj->getVX();
	oVy = obj->getVY();
	oAccelX = obj->getAccelX();
	oAccelY = obj->getAccelY();
	oGravity = 0;
	sizeHeight = obj->getSizeHeight();
	sizeWidth = obj->getSizeWidth();
	timeUpdate = obj->getTimeUpdate();
	timeAnimate = obj->getTimeAnimae();
}

bool MyObject::isCollision(MyObject* obj){
	if (getRect().isCollision(obj->getRect()))
	{
		return true;
	}
	return false;
}

int MyObject::DirectionCollision(MyObject* obj){
	if (isCollision(obj))
	{
		float top = fabs(this->getRect().top - obj->getRect().bottom);
		float bottom = fabs(this->getRect().bottom - obj->getRect().top);
		float left = fabs(this->getRect().left - obj->getRect().right);
		float right = fabs(this->getRect().right - obj->getRect().left);
		float dir = min(min(right, left), min(top,bottom));
		if (dir == top)
		{
			return TOP;
		}
		if (dir == bottom)
		{
			return BOTTOM;
		}
		if (dir == left)
		{
			return LEFT;
		}
		if (dir == right)
		{
			return RIGHT;
		}
	}
	return NONE;
}


