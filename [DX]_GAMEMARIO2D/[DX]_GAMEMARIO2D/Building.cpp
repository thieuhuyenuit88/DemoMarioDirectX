#include "Building.h"
#include "RSMainGame.h"

Building::Building(void): StaticObject(){
	Init();
}

Building::~Building(void){

}

void Building::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getBuildingSprite();
	iStaticSprite.setSize(500,550);
	iStaticSprite.setDepth(0.23f);

	oID = BUILDING;
	oSTT = ACTIVE;
	setSize(500,550);
}

void Building::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void Building::Realease(){
	StaticObject::Realease();
}