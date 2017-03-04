#include "Coin.h"
#include "RSMainGame.h"
#include "BrickBreak.h"
#include "EffectRenderScore.h"
#include "ManagerObject.h"
#include "InGameController.h"
#include "AudioManager.h"

Coin::Coin(void):DynamicObject(){
	rotaCoin = 0;
	Init();
}

Coin::Coin(Coin* obj):DynamicObject(obj){

}

Coin::~Coin(void){

}

void Coin::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getCoinSprite();
	iDynamicSprite.setSize(50,50);
	iDynamicSprite.setDepth(0.22f);

	setSize(50,50);
	oID = COIN;
}

void Coin::ProcessCollision(MyObject* obj){
	directCollision = DirectionCollision(obj);
	if (directCollision!= NONE)
	{
		switch(obj->getID())
		{
		case MARIO:
		case MARIO_BIG:
		case MARIO_SUPER:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE)
				{
					InGameController::getInGameController()->SCORE += 200;
					InGameController::getInGameController()->NUMBERCOIN += 1;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 200);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
					AudioManager::getAudioManager()->Play("e_coin");
					oSTT = BEFORE_DEATH;
				}
			}
			break;
		case BRICK_BREAK:
			if (oSTT == ACTIVE)
			{
				//If brick break is running up...
				if (obj->getSTT() == ACTIVE && ((BrickBreak*)obj)->isMoveUping)
				{
					if (directCollision == BOTTOM)
					{
						if (obj->getVY() != 0)
						{
							oVy = obj->getVY() + 0.02f;

							InGameController::getInGameController()->SCORE += 200;
							InGameController::getInGameController()->NUMBERCOIN += 1;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 200);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_coin");
							oSTT = BEFORE_DEATH;
						}
					}
				}
			}
			break;
		}
	}
}

void Coin::UpdateAnimation(float deltaTime){
	switch(oSTT){
	case ACTIVE:
		timeAnimate += deltaTime;
		if (timeAnimate > 200)
		{
			timeAnimate = 0;
			iDynamicSprite.AnimateNextFrame(0, 3);
		}
		break;
	case BEFORE_DEATH:
		timeAnimate += deltaTime;
		if (timeAnimate > 100)
		{
			timeAnimate = 0;
			iDynamicSprite.AnimateNextFrame(4, 4);
		}
		rotaCoin += 5;
		break;
	}
}

void Coin::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;

	if (oSTT == BEFORE_DEATH)
	{
		oVx += oAccelX*deltaTime;
		oVy += oAccelY*deltaTime;
		oPosX += oVx*deltaTime;
		oPosY += oVy*deltaTime;
	}
}

void Coin::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
	switch(oSTT){
	case BEFORE_DEATH:
		timeUpdate += deltaTime;
		if (timeUpdate > 500)
		{
			timeUpdate = 0;
			oSTT = DEATH;
		}
		break;
	}
}

void Coin::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void Coin::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	switch(oSTT){
	case ACTIVE:
		iDynamicSprite.setXY(oPosX, oPosY);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
		break;
	case BEFORE_DEATH:
		iDynamicSprite.setXY(oPosX, oPosY);
		iDynamicSprite.setRotation(rotaCoin);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
		break;
	}
}

void Coin::Realease(){
	DynamicObject::Realease();
}