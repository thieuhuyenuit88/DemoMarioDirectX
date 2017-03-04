#include "EffectBrickExplode.h"

EffectBrickExplode::EffectBrickExplode(void):Effect(){
	Init();
}

EffectBrickExplode::EffectBrickExplode(float x, float y):Effect(x,y){
	Init();
}

EffectBrickExplode::~EffectBrickExplode(void){

}

void EffectBrickExplode::Init(){
	listSpriteExplode = new vector<Break*>();
	for (int i = 0; i< 4; i++)
	{
		Break* breakExplode = new Break();
		breakExplode->setXY(oPosX + 25*(i%2), oPosY - 25*(i/2));
		if (i==0)
		{
			breakExplode->setVXVY(-0.5f, 0.6f);
		}
		else if (i==2)
		{
			breakExplode->setVXVY(-0.7f, 0.8f);
		}
		else if (i==1)
		{
			breakExplode->setVXVY(0.5f, 0.6f);
		}
		else
		{
			breakExplode->setVXVY(0.7f, 0.8f);
		}
		listSpriteExplode->push_back(breakExplode);
	}
	oSTT = ACTIVE;
}

void EffectBrickExplode::UpdateAnimation(float deltaTime){
	
}

void EffectBrickExplode::UpdateMove(float deltaTime){
	
}

void EffectBrickExplode::UpdateStatus(float deltaTime){
	switch(oSTT){
	case ACTIVE:
		timeEffect += deltaTime;
		if (timeEffect > g_TIME_EFFECT_BREAK)
		{
			timeEffect = 0;
			oSTT = DEATH;
		}
	break;
	}
}

void EffectBrickExplode::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
	for(vector<Break*>::iterator f = listSpriteExplode->begin(); f!=listSpriteExplode->end(); f++){
		(*f)->Update(deltaTime);
	}
}

void EffectBrickExplode::UpdateViewPosBeforeDraw(float interpolation){

}

void EffectBrickExplode::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	switch(oSTT){
	case ACTIVE:
		for(vector<Break*>::iterator f = listSpriteExplode->begin(); f!=listSpriteExplode->end(); f++){
			(*f)->Draw(spriteHandler, matrixWorld);
		}
		break;
	}
}
void EffectBrickExplode::Realease(){
	for(vector<Break*>::iterator f = listSpriteExplode->begin(); f!=listSpriteExplode->end(); f++){
		(*f)->Realease();
	}
	delete listSpriteExplode;
}