#include "StaticObject.h"

StaticObject::StaticObject(void):MyObject(){

}

StaticObject::~StaticObject(void){

}

StaticObject::StaticObject(StaticObject* obj){
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
	staticSprite = obj->getStaticSprite();
	iStaticSprite = obj->getISprite();
}

void StaticObject::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateStatus(deltaTime);
}

void StaticObject::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void StaticObject::Realease(){
}