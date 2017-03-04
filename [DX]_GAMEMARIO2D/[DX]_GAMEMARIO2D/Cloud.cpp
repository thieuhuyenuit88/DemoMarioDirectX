#include "Cloud.h"
#include "RSMainGame.h"

Cloud::Cloud(void): StaticObject(){
	Init();
}

Cloud::~Cloud(void){

}

void Cloud::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getCloudSprite();
	iStaticSprite.setSize(100, 80);
	iStaticSprite.setDepth(0.25f);

	oID = CLOUD;
	oSTT = ACTIVE;
	setSize(100, 80);
}

void Cloud::UpdateAnimation(float deltaTime){
	timeAnimate += deltaTime;
	if (timeAnimate > 100)
	{
		timeAnimate = 0;
		iStaticSprite.AnimateNextFrame(0, 3);
	}
}

void Cloud::Update(float deltaTime){
	UpdateAnimation(deltaTime);
}

void Cloud::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void Cloud::Realease(){
	StaticObject::Realease();
}