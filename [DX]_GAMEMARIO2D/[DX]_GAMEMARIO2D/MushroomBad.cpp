#include "MushroomBad.h"
#include "RSMainGame.h"
#include "CLog.h"
#include "Mario.h"
#include "Turtle.h"
#include "EffectRenderScore.h"
#include "ManagerObject.h"
#include "InGameController.h"
#include "AudioManager.h"
#include "CollisionDetect.h"

MushroomBad::MushroomBad(void):DynamicObject(){
	isBeforeDeathFlatted = isBeforteDeathJumpUp = false;
	Init();
}

MushroomBad::~MushroomBad(void){

}

MushroomBad::MushroomBad(MushroomBad* obj):DynamicObject(obj){
	isBeforeDeathFlatted = obj->isBeforeDeathFlatted;
	isBeforteDeathJumpUp = obj->isBeforteDeathJumpUp;
}

void MushroomBad::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getMushroomBad();
	iDynamicSprite.setSize(50,50);
	iDynamicSprite.setDepth(0.08f);

	oDirect = 1;
	oID = MUSHROOM_BAD;
	oAccelY = -0.001f;
	oVy = oAccelY * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
	oSTT = ACTIVE;
	setSize(48,48);
}

void MushroomBad::ProcessCollision(MyObject* obj, int _dir){
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
				if (oSTT == ACTIVE)
				{
					/*if (((Mario*)obj)->isNomaling || ((Mario*)obj)->isShotting)
					{*/
						if (directCollision == TOP)
						{
							InGameController::getInGameController()->SCORE += 100;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 100);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_mush_die");
							oSTT = BEFORE_DEATH;
							setBeforeDeathFlatted();
						}
					//}
					/*else if (((Mario*)obj)->isInving || ((Mario*)obj)->isDowning || ((Mario*)obj)->isUpping)
					{
						if (directCollision == LEFT)
						{
							if (oVy < 0)
							{
								oVx *= -1;
								oPosX = obj->getPosX() + obj->getSizeWidth();
							}
						}else
						if (directCollision == RIGHT)
						{
							if (oVx > 0)
							{
								oVx *= -1;
								oPosX = obj->getPosX() - sizeWidth;
							}
						}
					}*/
				}
			}
			break;
		case BULLET_MARIO:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE)
				{
					//death with jump up
					oVy = 0.4f;
					oSTT = BEFORE_DEATH;
					setBeforeDeathJumpUp();

					InGameController::getInGameController()->SCORE += 100;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 100);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
					AudioManager::getAudioManager()->Play("e_death_shot");
				}
			}
			break;
		}
	}
	directCollision = NONE;
}

void MushroomBad::ProcessCollision(MyObject* obj){
	directCollision = NONE;
	float collisionTime;
	float normalx, normaly;

	collisionTime = CollisionDetect::getCollisionDetect()->CollisionDir(this, obj, normalx, normaly);
	if (collisionTime != 1.0f)
	{
		if (normalx == 1.0f && normaly == 0.0f)
		{
			directCollision = LEFT;
		}else
			if (normaly == 1.0f && normalx == 0.0f)
			{
				directCollision = BOTTOM;
			}else
				if (normalx == -1.0f && normaly == 0.0f)
				{
					directCollision = RIGHT;

				}else
					if (normaly == -1.0f && normalx == 0.0f)
					{
						directCollision = TOP;
					}else
						if (normalx == 1.0f && normaly == -1.0f)
						{
							directCollision = TOP_LEFT;
						}else
							if (normalx == 1.0f && normaly == 1.0f)
							{
								directCollision = BOTTOM_LEFT;
							}
							else
								if (normalx == -1.0f && normaly == -1.0f)
								{
									directCollision = TOP_RIGHT;
								}
								else
									if (normalx == -1.0f && normaly == 1.0f)
									{
										directCollision = BOTTOM_RIGHT;
									}
	}else{
		directCollision = DirectionCollision(obj);
	} 
	//directCollision = DirectionCollision(obj);
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
					/*if (((Mario*)obj)->isNomaling || ((Mario*)obj)->isShotting)
					{*/
						if (directCollision == TOP)
						{
							InGameController::getInGameController()->SCORE += 100;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 100);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_mush_die");
							oSTT = BEFORE_DEATH;
							setBeforeDeathFlatted();
						}
					//}
					/*else if (((Mario*)obj)->isInving || ((Mario*)obj)->isDowning || ((Mario*)obj)->isUpping)
					{
						if (directCollision == LEFT)
						{
							if (oVy < 0)
							{
								oVx *= -1;
								oPosX = obj->getPosX() + obj->getSizeWidth();
							}
						}else
						if (directCollision == RIGHT)
						{
							if (oVx > 0)
							{
								oVx *= -1;
								oPosX = obj->getPosX() - sizeWidth;
							}
						}
					}*/
				}
			}
			break;
		case PIPE:
		case LAND_BASE:
		case BRICK_BREAK:
		case BRICK_HARD:
		case QUESTION_BRICK:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE)
				{
					if (directCollision == BOTTOM)
					{
						if (obj->getVY() != 0)
						{
							//death with jump up
							oVy = 0.4f;
							oSTT = BEFORE_DEATH;
							setBeforeDeathJumpUp();

							InGameController::getInGameController()->SCORE += 100;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 100);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_death_shot");
						}else{
							oPosY += collisionTime * oVy*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() -
								oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();//obj->getPosY() + sizeHeight + 0.6f;
							oVy = 0;
						}
					}

					if (directCollision == BOTTOM_LEFT || directCollision == BOTTOM_RIGHT)
					{
						oPosY -= oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						oVy = 0;
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
					}

					if (directCollision == LEFT)
					{
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						if (oDirect < 0)
						{
							oDirect *= -1;
						}
					}

					if (directCollision == RIGHT)
					{
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						if (oDirect > 0)
						{
							oDirect *= -1;
						}
					}
				}
			}
			break;
		case TURTLE:
			if (oSTT == ACTIVE)
			{
				if (obj->getSTT() == ACTIVE)
				{
					if (((Turtle*)obj)->isRunning)
					{
						//death with jump up
						oVy = 0.4f;
						oSTT = BEFORE_DEATH;
						setBeforeDeathJumpUp();

						InGameController::getInGameController()->SCORE += 100;
						EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 100);
						ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
						AudioManager::getAudioManager()->Play("e_death_shot");
					}else if (((Turtle*)obj)->isStaticing)
					{
						if (directCollision == LEFT)
						{
							oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
							if (oDirect < 0)
							{
								oDirect *= -1;
							}
						}
						else
						if (directCollision == RIGHT)
						{
							oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
							if (oDirect > 0)
							{
								oDirect *= -1;
							}
						}
					}
				}
			}
			break;
		case BULLET_MARIO:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE)
				{
					//death with jump up
					oVy = 0.4f;
					oSTT = BEFORE_DEATH;
					setBeforeDeathJumpUp();

					InGameController::getInGameController()->SCORE += 100;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 100);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
					AudioManager::getAudioManager()->Play("e_death_shot");
				}
			}
			break;
		}
	}
	directCollision = NONE;
}

void MushroomBad::UpdateAnimation(float deltaTime){
	switch (oSTT)
	{
	case ACTIVE:
		timeAnimate += deltaTime;
		if (timeAnimate >= 200)
		{
			timeAnimate = 0;
			iDynamicSprite.setCurFrame((iDynamicSprite.getCurFrame()+1) % 2);
		}
		break;
	case BEFORE_DEATH:
		if (isBeforeDeathFlatted)
		{
			iDynamicSprite.setCurFrame(2);
		}
		break;
	}
}

void MushroomBad::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;

	if (oSTT == ACTIVE || (oSTT == BEFORE_DEATH && isBeforteDeathJumpUp))
	{
		oVx = oDirect* 0.05f;

		oVx += oAccelX*deltaTime;
		oVy += oAccelY*deltaTime;
		oPosX += oVx*deltaTime;
		oPosY += oVy*deltaTime;

		if (oPosY < 0 && prevPosY <= 0)
		{
			oSTT = DEATH;
		}
	}
}

void MushroomBad::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
	if (oSTT == BEFORE_DEATH)
	{
		timeUpdate += deltaTime;
		if (timeUpdate >= 1500)
		{
			timeUpdate = 0;
			oSTT = DEATH;
		}
	}
}

void MushroomBad::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void MushroomBad::UpdateViewPosBeforeDraw(float interpolation){

}

void MushroomBad::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	if (oSTT == ACTIVE || (oSTT == BEFORE_DEATH && isBeforeDeathFlatted))
	{
		iDynamicSprite.setXY(oPosX, oPosY);
		iDynamicSprite.setScaleXY(1,1);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
	}else if (oSTT == BEFORE_DEATH && isBeforteDeathJumpUp)
	{
		iDynamicSprite.setXY(oPosX, oPosY);
		iDynamicSprite.setScaleXY(1, -1);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
	}
}

void MushroomBad::Realease(){
	DynamicObject::Realease();
}