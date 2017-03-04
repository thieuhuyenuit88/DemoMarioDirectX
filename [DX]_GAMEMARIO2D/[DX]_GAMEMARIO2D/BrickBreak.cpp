#include "BrickBreak.h"
#include "RSMainGame.h"
#include "CLog.h"
#include "EffectBrickExplode.h"
#include "ManagerObject.h"
#include "EffectBossExplode.h"
#include "AudioManager.h"

BrickBreak::BrickBreak(void):DynamicObject(){
	
	Init();
}

BrickBreak::~BrickBreak(void){

}

BrickBreak::BrickBreak(BrickBreak* obj):DynamicObject(obj){
	startPosY = obj->getStartY();
	isNormaling = obj->isNormaling;
	isMoveUping = obj->isMoveUping;
	isMovingUpWithDeath = obj->isMovingUpWithDeath;
}

void BrickBreak::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getBrickBreakSprite();
	iDynamicSprite.setSize(50,50);
	iDynamicSprite.setCurFrame(0);
	iDynamicSprite.setDepth(0.9f);

	oID = BRICK_BREAK;
	oAccelY = g_ACCELY;
	oSTT = ACTIVE;
	setSize(50,50);

	setNormaling();
}

void BrickBreak::ProcessCollision(MyObject* obj, int _dir){
	if (_dir != NONE)
	{
		if (_dir == LEFT)
		{
			directCollision = RIGHT;
		}
		if (_dir == RIGHT)
		{
			directCollision = LEFT;
		}
		if (_dir == TOP)
		{
			directCollision = BOTTOM;
		}
		if (_dir == BOTTOM || _dir == BOTTOM_LEFT || _dir == BOTTOM_RIGHT)
		{
			directCollision = TOP;
		}
	}else{
		directCollision = NONE;
	}
	if (directCollision!= NONE)
	{
		switch(obj->getID()){
		case MARIO:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE && directCollision == BOTTOM)
				{
					setMoveUp();
					AudioManager::getAudioManager()->Play("e_brick_up");
				}
			}
			break;
		case MARIO_BIG:
		case MARIO_SUPER:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE && directCollision == BOTTOM && !isMovingUpWithDeath)
				{
					EffectBrickExplode* effBrickExplode = new EffectBrickExplode(oPosX, oPosY);
					ManagerObject::getManagerObject()->getListEffect()->push_back(effBrickExplode);
					AudioManager::getAudioManager()->Play("e_broken");
					if (!isMovingUpWithDeath)
					{
						oVy = g_VY_MOVE_UP;
						setMovingUpWithDeath();
					}
				}
			}
			break;
		}
	}
}

void BrickBreak::ProcessCollision(MyObject* obj){
	directCollision = DirectionCollision(obj);
	if(directCollision != NONE){
		switch(obj->getID()){
		case MARIO:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE && directCollision == BOTTOM)
				{
					setMoveUp();
					AudioManager::getAudioManager()->Play("e_brick_up");
				}
			}
			break;
		case MARIO_BIG:
		case MARIO_SUPER:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE && directCollision == BOTTOM && !isMovingUpWithDeath)
				{
					EffectBrickExplode* effBrickExplode = new EffectBrickExplode(oPosX, oPosY);
					ManagerObject::getManagerObject()->getListEffect()->push_back(effBrickExplode);
					AudioManager::getAudioManager()->Play("e_broken");
					if (!isMovingUpWithDeath)
					{
						oVy = g_VY_MOVE_UP;
						setMovingUpWithDeath();
					}
				}
			}
			break;
		}
	}
}

void BrickBreak::UpdateAnimation(float deltaTime){

}

void BrickBreak::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;

	switch(oSTT){
	case ACTIVE:
		if (isMoveUping || isMovingUpWithDeath)
		{
			oVy += oAccelY * deltaTime;

			oPosY += oVy*deltaTime;

			nextPosY = oPosY + oVy*deltaTime;

			//fall down not more than old value - check by position in next frame
			if (oVy != 0)
			{
				if (oPosY <= startPosY)
				{
					oPosY = startPosY;
					oVy = 0;
					if (isMoveUping)
					{
						setNormaling();
					}else if (isMovingUpWithDeath)
					{
						isMovingUpWithDeath = false;
						oSTT = DEATH;
					}

				}
			}	
		}
		break;
	}
}

void BrickBreak::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
	/*switch(oSTT){
	case ACTIVE:
	if (isMovingUpWithDeath)
	{
	timeUpdate += deltaTime;
	if (timeUpdate >= 500)
	{
	timeUpdate = 0;
	isMovingUpWithDeath = false;
	oSTT = DEATH;
	}
	}
	break;
	}*/
}

void BrickBreak::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void BrickBreak::UpdateViewPosBeforeDraw(float interpolation){

}

void BrickBreak::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	switch(oSTT){
	case ACTIVE:
		if (isNormaling || isMoveUping)
		{
			iDynamicSprite.setXY(oPosX, oPosY);
			dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
		}
		break;
	}
}

void BrickBreak::Realease(){

}

void BrickBreak::setMoveUp(){
	if (!isMoveUping)
	{
		oVy = g_VY_MOVE_UP;
		setMoveUping();
	}
}

