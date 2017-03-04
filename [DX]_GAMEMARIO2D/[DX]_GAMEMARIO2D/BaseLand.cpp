#include "BaseLand.h"
#include "RSMainGame.h"

BaseLand::BaseLand(void): StaticObject(){
	Init();
}

BaseLand::~BaseLand(void){

}

void BaseLand::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getBaseLandSprite();
	iStaticSprite.setSize(50,50);
	iStaticSprite.setDepth(0.1f);

	oID = LAND_BASE;
	oSTT = ACTIVE;
	setSize(50,50);
}

void BaseLand::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void BaseLand::Realease(){
	StaticObject::Realease();
}