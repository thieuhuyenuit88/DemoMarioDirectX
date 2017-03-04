#include "BossBreak.h"
#include "RSMainGame.h"
#include <d3dx9.h>

BossBreak::BossBreak(void):DynamicObject(){
	Init();
}

BossBreak::~BossBreak(void){

}

void BossBreak::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getBossBreakSprite();
	iDynamicSprite.setSize(25,22);
	iDynamicSprite.setDepth(0.03f);

	rotationBreak = 0;
}

void BossBreak::UpdateAnimation(float deltaTime){
	rotationBreak += deltaTime;
}

void BossBreak::UpdateMove(float deltaTime){
	oVx += oAccelX*deltaTime;
	oVy += oAccelY*deltaTime;
	oPosX += oVx*deltaTime;
	oPosY += oVy*deltaTime;
}

void BossBreak::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
}

void BossBreak::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void BossBreak::UpdateViewPosBeforeDraw(float interpolation){

}

void BossBreak::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iDynamicSprite.setXY(oPosX, oPosY);
	iDynamicSprite.setRotation(rotationBreak);
	dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
}

void BossBreak::Realease(){
	DynamicObject::Realease();
}