#include "Winpole.h"
#include "RSMainGame.h"

Winpole::Winpole(void): StaticObject(){
	Init();
}

Winpole::~Winpole(void){

}

void Winpole::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getWinpoleSprite();
	iStaticSprite.setSize(50,450);
	iStaticSprite.setDepth(0.19f);

	oID = WINPOLE;
	oSTT = ACTIVE;
	setSize(50,450);
}

void Winpole::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void Winpole::Realease(){
	StaticObject::Realease();
}