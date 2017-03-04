#include "QuestionBrick.h"
#include "RSMainGame.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Flower.h"
#include "InGameController.h"
#include "ManagerObject.h"
#include "EffectRenderScore.h"
#include "AudioManager.h"

QuestionBrick::QuestionBrick(void): DynamicObject(){
	Init();
}

QuestionBrick::~QuestionBrick(void){

}

QuestionBrick::QuestionBrick(QuestionBrick* obj):DynamicObject(obj){
	isNormaling = obj->isNormaling;
	isStaticing = obj->isStaticing;
	hideObject = obj->getHideObject();
}

void QuestionBrick::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getQuestionBrickSprite();
	iDynamicSprite.setSize(50,50);
	iDynamicSprite.setDepth(0.18f);

	oID = QUESTION_BRICK;
	oSTT = ACTIVE;
	setSize(50,50);
	setNormaling();
}

void QuestionBrick::ProcessCollision(MyObject* obj, int _dir){
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
		switch(obj->getID())
		{
		case MARIO:
		case MARIO_BIG:
		case MARIO_SUPER:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE && isNormaling)
				{
					if (directCollision == BOTTOM)
					{
						switch(hideObject->getID()){
						case MUSHROOMUP:
							hideObject->setSTT(ACTIVE);
							((Mushroom*)hideObject)->setUpping();
							AudioManager::getAudioManager()->Play("e_up");
							hideObject->setVY(0.018f);
							break;
						case MUSHROOMBIG:
							hideObject->setSTT(ACTIVE);
							((Mushroom*)hideObject)->setUpping();
							AudioManager::getAudioManager()->Play("e_up");
							hideObject->setVY(0.018f);
							break;
						case FLOWER:
							hideObject->setSTT(ACTIVE);
							((Flower*)hideObject)->setUpping();
							AudioManager::getAudioManager()->Play("e_up");
							hideObject->setVY(0.018f);
							break;
						case COIN:
							InGameController::getInGameController()->SCORE += 200;
							InGameController::getInGameController()->NUMBERCOIN += 1;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 200);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_coin");

							hideObject->setSTT(BEFORE_DEATH);
							hideObject->setAccelY(-0.001f);
							hideObject->setVY(0.5f);
							break;
						}
						setStaticing();
					}
				}
			}
			break;
		}
	}
}

void QuestionBrick::ProcessCollision(MyObject* obj){
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
				if (oSTT == ACTIVE && isNormaling)
				{
					if (directCollision == BOTTOM)
					{
						switch(hideObject->getID()){
						case MUSHROOMUP:
							hideObject->setSTT(ACTIVE);
							((Mushroom*)hideObject)->setUpping();
							AudioManager::getAudioManager()->Play("e_up");
							hideObject->setVY(0.018f);
							break;
						case MUSHROOMBIG:
							hideObject->setSTT(ACTIVE);
							((Mushroom*)hideObject)->setUpping();
							AudioManager::getAudioManager()->Play("e_up");
							hideObject->setVY(0.018f);
							break;
						case FLOWER:
							hideObject->setSTT(ACTIVE);
							((Flower*)hideObject)->setUpping();
							AudioManager::getAudioManager()->Play("e_up");
							hideObject->setVY(0.018f);
							break;
						case COIN:
							InGameController::getInGameController()->SCORE += 200;
							InGameController::getInGameController()->NUMBERCOIN += 1;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 200);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_coin");

							hideObject->setSTT(BEFORE_DEATH);
							hideObject->setAccelY(-0.001f);
							hideObject->setVY(0.5f);
							break;
						}
						setStaticing();
					}
				}
			}
			break;
		}
	}
}

void QuestionBrick::UpdateAnimation(float deltaTime){
	switch(oSTT){
	case ACTIVE:
		if (isNormaling)
		{
			timeAnimate += deltaTime;
			if (timeAnimate > 200)
			{
				timeAnimate = 0;
				iDynamicSprite.AnimateNextFrame(1,2);
			}
		}else
		if (isStaticing)
		{
			iDynamicSprite.setCurFrame(0);
		}
		break;
	}
}

void QuestionBrick::Update(float deltaTime){
	UpdateAnimation(deltaTime);
}

void QuestionBrick::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iDynamicSprite.setXY(oPosX, oPosY);
	dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
}

void QuestionBrick::Realease(){
	DynamicObject::Realease();
}