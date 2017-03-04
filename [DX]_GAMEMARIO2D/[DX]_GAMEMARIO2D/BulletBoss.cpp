#include "BulletBoss.h"
#include "RSMainGame.h"

BulletBoss::BulletBoss(void): Skill(){
	Init();
}

BulletBoss::BulletBoss(float x, float y):Skill(x, y)
{
	Init();
}

BulletBoss::BulletBoss(BulletBoss* obj):Skill(obj){

}

BulletBoss::~BulletBoss(void){

}

void BulletBoss::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getBulletBossSprite();
	iDynamicSprite.setSize(89,50);
	iDynamicSprite.setDepth(0.1f);

	oID = BULLET_BOSS;
	oVx = 0.6f;
	oSTT = ACTIVE;
	setSize(89,50);
}

void BulletBoss::ProcessCollision(MyObject* obj){
	directCollision = NONE;
	directCollision = DirectionCollision(obj);
	if (directCollision!= NONE)
	{
		switch(obj->getID())
		{
		case BRICK_BREAK:
		case BRICK_HARD:
		case PIPE:
		case LAND_BASE:
		case QUESTION_BRICK:
		case MARIO:
		case MARIO_BIG:
		case MARIO_SUPER:
			if (oSTT == ACTIVE)
			{
				if (obj->getSTT() == ACTIVE)
				{
					oSTT = DEATH;
				}
			}
			break;
		}
	}
}

void BulletBoss::UpdateAnimation(float deltaTime){
	switch(oSTT){
	case ACTIVE:
		timeAnimate += deltaTime;
		if (timeAnimate > 100)
		{
			timeAnimate = 0;
			iDynamicSprite.AnimateNextFrame(0, 3);
		}
		break;
	}
}

void BulletBoss::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
}

void BulletBoss::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;

	if (oSTT == ACTIVE)
	{
		oVx += oAccelX*deltaTime;
		oVy += oAccelY*deltaTime;
		oPosX += oVx*deltaTime;
		oPosY += oVy*deltaTime;
	}
}

void BulletBoss::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}


void BulletBoss::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	if (oSTT == ACTIVE)
	{
		iDynamicSprite.setXY(oPosX, oPosY);
		iDynamicSprite.setScaleXY(oDirect, 1);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
	}
}

void BulletBoss::Realease(){
	Skill::Realease();
}
