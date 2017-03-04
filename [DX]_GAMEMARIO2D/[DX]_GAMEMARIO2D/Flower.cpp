#include "Flower.h"
#include "RSMainGame.h"
#include "InGameController.h"
#include "EffectRenderScore.h"
#include "ManagerObject.h"

Flower::Flower(void):DynamicObject(){
	Init();
}

Flower::~Flower(void){

}

Flower::Flower(Flower* obj):DynamicObject(obj){
	startPosY = obj->getStartPosY();
}

void Flower::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getFlowerSprite();
	iDynamicSprite.setSize(50,50);
	iDynamicSprite.setDepth(0.2f);

	setSize(50,50);
	oID = FLOWER;
	oSTT = READY;
	isNormaling = isUpping = false;
}

void Flower::ProcessCollision(MyObject* obj,int _dir){
	directCollision = _dir;
	if (directCollision!= NONE)
	{
		switch(obj->getID())
		{
		case MARIO:
		case MARIO_BIG:
		case MARIO_SUPER:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE && !isUpping)
				{
					oSTT = DEATH;

					InGameController::getInGameController()->SCORE += 500;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 500);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);

					if (oID == MUSHROOMUP)
					{
						InGameController::getInGameController()->LIFE += 1;
					}
				}
			}
			break;
		}
	}
}

void Flower::ProcessCollision(MyObject* obj){
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
				if (oSTT == ACTIVE && !isUpping)
				{
					oSTT = DEATH;

					InGameController::getInGameController()->SCORE += 500;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 500);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);

					if (oID == MUSHROOMUP)
					{
						InGameController::getInGameController()->LIFE += 1;
					}
				}
			}
			break;
		}
	}
}

void Flower::UpdateAnimation(float deltaTime){
	switch (oSTT)
	{
	case ACTIVE:
		timeAnimate+=deltaTime;
		if (timeAnimate > 200)
		{
			iDynamicSprite.AnimateNextFrame(0,4);
			timeAnimate = 0;
		}
		break;
	}
}

void Flower::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;
	switch(oSTT){
	case ACTIVE:
		if (isUpping)
		{
			oPosY += oVy*deltaTime;
		}else if (isNormaling)
		{
			oVx += oAccelX*deltaTime;
			oVy += oAccelY*deltaTime;
			oPosX += oVx*deltaTime;
			oPosY += oVy*deltaTime;
		}
		break;
	}
}

void Flower::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
	switch(oSTT){
	case ACTIVE:
		if (isUpping)
		{
			if (oPosY > startPosY + sizeHeight)
			{
				oPosY = startPosY + sizeHeight;
				setVXVY(0.0f,0.0f);
				setNormaling();
			}
		}
		break;
	}
}

void Flower::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void Flower::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	if (oSTT == ACTIVE)
	{
		iDynamicSprite.setXY(oPosX, oPosY);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
	}
}

void Flower::Realease(){
	DynamicObject::Realease();
}