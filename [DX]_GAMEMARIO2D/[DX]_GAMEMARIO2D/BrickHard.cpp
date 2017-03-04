#include "BrickHard.h"
#include "RSMainGame.h"

BrickHard::BrickHard(void): StaticObject(){
	Init();
}

BrickHard::~BrickHard(void){

}

void BrickHard::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getBrickSprite();
	iStaticSprite.setSize(50,50);
	iStaticSprite.setDepth(0.1f);

	oID = BRICK_HARD;
	oSTT = ACTIVE;
	setSize(50,50);
}

void BrickHard::ProcessCollision(MyObject* obj){

}

void BrickHard::UpdateAnimation(float deltaTime){

}

void BrickHard::UpdateStatus(float deltaTime){

}

void BrickHard::Update(float deltaTime){

}

void BrickHard::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void BrickHard::Realease(){
	StaticObject::Realease();
}