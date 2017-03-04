#include "Fence.h"
#include "RSMainGame.h"

Fence::Fence(void): StaticObject(){
	Init();
}

Fence::~Fence(void){

}

void Fence::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getFenceSprite();
	iStaticSprite.setSize(50,50);
	iStaticSprite.setDepth(0.2f);

	oID = FENCE;
	oSTT = ACTIVE;
	setSize(50,50);
}

void Fence::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void Fence::Realease(){
	StaticObject::Realease();
}
