#include "Break.h"
#include "RSMainGame.h"
#include <d3dx9.h>

Break::Break(void):DynamicObject(){
	Init();
}

Break::~Break(void){

}

void Break::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getBrickExplode();
	iDynamicSprite.setSize(25,25);
	iDynamicSprite.setDepth(0.04f);

	oAccelY = -0.004f;//g_ACCELY;
	rotationBreak = 0;
}

void Break::UpdateAnimation(float deltaTime){
	rotationBreak += 5;
}

void Break::UpdateMove(float deltaTime){
	oVx += oAccelX*deltaTime;
	oVy += oAccelY*deltaTime;
	oPosX += oVx*deltaTime;
	oPosY += oVy*deltaTime;
}

void Break::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
}

void Break::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void Break::UpdateViewPosBeforeDraw(float interpolation){

}

void Break::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iDynamicSprite.setXY(oPosX, oPosY);
	iDynamicSprite.setRotation(rotationBreak);
	dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
}

void Break::Realease(){
	DynamicObject::Realease();
}