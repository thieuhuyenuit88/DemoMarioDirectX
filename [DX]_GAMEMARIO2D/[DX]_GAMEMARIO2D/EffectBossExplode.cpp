#include "EffectBossExplode.h"

EffectBossExplode::EffectBossExplode(void):Effect(){
	Init();
}

EffectBossExplode::EffectBossExplode(float x, float y):Effect(x,y){
	Init();
}

EffectBossExplode::~EffectBossExplode(void){

}

void EffectBossExplode::Init(){
	listSpriteExplode = new vector<BossBreak*>();
	for (int i = 0; i < 20; i++)
	{
		BossBreak* breakExplode = new BossBreak();
		breakExplode->setCurFrame(i);
		breakExplode->setXY(oPosX + 25*(i%4), oPosY - 22*(i/5));

		if (i==1 || i==2)
		{
			breakExplode->setVXVY(0, 0.6f);
		}
		else if (i==17 || i==18)
		{
			breakExplode->setVXVY(0, -0.6f);
		}
		else if (i==0 || i==4)
		{
			breakExplode->setVXVY(-0.5f, 0.6f);
		}
		else if (i==3 || i==7)
		{
			breakExplode->setVXVY(0.5f, 0.6f);
		}
		else if (i==16 || i==12)
		{
			breakExplode->setVXVY(-0.5f, -0.6f);
		}
		else if (i==19 || i==15)
		{
			breakExplode->setVXVY(0.5f, -0.6f);
		}
		else if (i==8 || i==9)
		{
			breakExplode->setVXVY(-0.5f, 0);
		}
		else if (i==10 || i==11)
		{
			breakExplode->setVXVY(0.5f, 0);
		}
		listSpriteExplode->push_back(breakExplode);
	}
	oSTT = ACTIVE;
}

void EffectBossExplode::UpdateAnimation(float deltaTime){

}

void EffectBossExplode::UpdateMove(float deltaTime){

}

void EffectBossExplode::UpdateStatus(float deltaTime){
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

void EffectBossExplode::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
	for(vector<BossBreak*>::iterator f = listSpriteExplode->begin(); f!=listSpriteExplode->end(); f++){
		(*f)->Update(deltaTime);
	}
}

void EffectBossExplode::UpdateViewPosBeforeDraw(float interpolation){

}

void EffectBossExplode::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	switch(oSTT){
	case ACTIVE:
		for(vector<BossBreak*>::iterator f = listSpriteExplode->begin(); f!=listSpriteExplode->end(); f++){
			(*f)->Draw(spriteHandler, matrixWorld);
		}
		break;
	}
}
void EffectBossExplode::Realease(){
	for(vector<BossBreak*>::iterator f = listSpriteExplode->begin(); f!=listSpriteExplode->end(); f++){
		(*f)->Realease();
	}

	delete listSpriteExplode;
}