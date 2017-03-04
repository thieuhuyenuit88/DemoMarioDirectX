#include "Grass.h"
#include "RSMainGame.h"

Grass::Grass(void): StaticObject(){
	Init();
}

Grass::~Grass(void){

}

void Grass::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getGrassSprite();
	iStaticSprite.setSize(100, 50);
	iStaticSprite.setDepth(0.22f);

	oID = GRASS;
	oSTT = ACTIVE;
	setSize(100, 50);
}

void Grass::UpdateAnimation(float deltaTime){
	timeAnimate += deltaTime;
	if (timeAnimate > 200)
	{
		timeAnimate = 0;
		iStaticSprite.AnimateNextFrame(0, 3);
	}
}

void Grass::Update(float deltaTime){
	UpdateAnimation(deltaTime);
}

void Grass::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void Grass::Realease(){
	StaticObject::Realease();
}