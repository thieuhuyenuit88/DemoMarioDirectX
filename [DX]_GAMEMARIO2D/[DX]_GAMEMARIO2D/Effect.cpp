#include "Effect.h"

Effect::Effect(void):MyObject(){
	timeEffect = 0;
}

Effect::Effect(float x, float y){
	oID = 0;
	oDirect = 0;
	oSTT = 0;
	oOldSTT = 0;
	oPosX = x;
	oPosY = y;
	oVx = 0;
	oVy = 0;
	oDirect = 0;
	oAccelX = 0;
	oAccelY = 0;
	oGravity = 0;
	sizeHeight = sizeWidth = 0;
	timeUpdate = timeAnimate = 0;
	timeEffect = 0;
}

Effect::~Effect(void){

}
