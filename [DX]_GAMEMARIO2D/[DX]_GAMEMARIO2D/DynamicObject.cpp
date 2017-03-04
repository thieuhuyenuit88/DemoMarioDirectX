#include "DynamicObject.h"

DynamicObject::DynamicObject(void): MyObject(){
	nextPosX = nextPosY = nextVx = nextVy = 0;
	prevPosX = prevPosY = 0;
}

DynamicObject::~DynamicObject(void){

}

DynamicObject::DynamicObject(DynamicObject* obj){
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
	dynamicSprite = obj->getDynamicSprite();
	iDynamicSprite = obj->getISprite();
	prevPosX = obj->getPrevPosX();
	prevPosY = obj->getPrevPosY();
}

bool DynamicObject::isCollision(MyObject* obj){
	if (getRect().isCollision(obj->getRect()))
	{
		return true;
	}
	/*if ((this->getRect().isCollision(obj->getRect()) && !this->getPrevRect().isCollision(obj->getRect())) ||
		(this->getRect().isCollision(obj->getRect()) && this->getPrevRect().isCollision(obj->getRect())))
	{
		return true;
	}*/
	/*else if (this->getNextRect().isCollision(obj->getRect()))
	{
		return true;
	}*/
	return false;
}

void DynamicObject::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;

	oVx += oAccelX*deltaTime;
	oVy += oAccelY*deltaTime;
	oPosX += oVx*deltaTime;
	oPosY += oVy*deltaTime;

	/*nextVx = oVx + oAccelX*deltaTime;
	nextVy = oVy + oAccelY*deltaTime;
	nextPosX = oPosX + oVx*deltaTime;
	nextPosY = oPosY + oVy*deltaTime;*/
}

void DynamicObject::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void DynamicObject::UpdateViewPosBeforeDraw(float interpolation){
	oVxView = oVx + oAccelX*interpolation;
	oVyView = oVy + oAccelY*interpolation;
	oPosViewX = oPosX + oVxView*interpolation;
	oPosViewY = oPosY + oVyView*interpolation;
}

void DynamicObject::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iDynamicSprite.setXY(oPosX, oPosY);
	dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
}

void DynamicObject::Realease(){
}