#include "Pole.h"
#include "RSMainGame.h"

Pole::Pole(void): StaticObject(){
	Init();
}

Pole::~Pole(void){

}

void Pole::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getPoleSprite();
	iStaticSprite.setSize(50,50);
	iStaticSprite.setDepth(0.19f);

	oID = POLE;
	oSTT = ACTIVE;
	setSize(50,50);
}

void Pole::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void Pole::Realease(){
	StaticObject::Realease();
}
