#include "Post.h"
#include "RSMainGame.h"

Post::Post(void): StaticObject(){
	Init();
}

Post::~Post(void){

}

void Post::Init(){
	staticSprite = RSMainGame::getRSMainGame()->getPostSprite();
	iStaticSprite.setSize(50,50);
	iStaticSprite.setDepth(0.19f);

	oID = POST;
	oSTT = ACTIVE;
	setSize(50,50);
}

void Post::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iStaticSprite.setXY(oPosX, oPosY);
	staticSprite->Draw(spriteHandler, matrixWorld, iStaticSprite);
}

void Post::Realease(){
	StaticObject::Realease();
}
