#include "Pipe.h"
#include "RSMainGame.h"

Pipe::Pipe(void): StaticObject(){
	Init();
}

Pipe::~Pipe(void){

}

void Pipe::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getPipeSprite();
	iStaticSprite.setSize(50,50);
	iStaticSprite.setDepth(0.1f);

	oID = PIPE;
	oSTT = ACTIVE;
	setSize(50,50);
}

void Pipe::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void Pipe::Realease(){
	StaticObject::Realease();
}
