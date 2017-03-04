#include "Turtle.h"
#include "RSMainGame.h"
#include "BrickBreak.h"
#include "EffectRenderScore.h"
#include "ManagerObject.h"
#include "InGameController.h"
#include "AudioManager.h"
#include "CollisionDetect.h"

Turtle::Turtle(void): DynamicObject(){
	setNormaling();
	Init();
}

Turtle::~Turtle(void){

}

Turtle::Turtle(Turtle* obj):DynamicObject(obj){
	isNormaling = obj->isNormaling;
	isRunning = obj->isRunning;
	isStaticing = obj->isStaticing;
}

void Turtle::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getTurtleSprite();
	iDynamicSprite.setSize(50,72);
	iDynamicSprite.setDepth(0.06f);

	oDirect = -1;
	oID = TURTLE;
	oAccelY = -0.001f;
	oVy = oAccelY * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
	oSTT = ACTIVE;
	setSize(48, 70);
}

void Turtle::ProcessCollision(MyObject* obj, int _dir){
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
	}
	else{
		directCollision = DirectionCollision(obj);
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
					if ((isNormaling || isRunning) && directCollision == TOP)
					{
						if (isNormaling)
						{
							InGameController::getInGameController()->SCORE += 100;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 100);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_mush_die");
						}

						setStaticing();
						oVx = 0;
						setSize(50,50);
						iDynamicSprite.setSize(46,46);
					}else
						if (isStaticing && directCollision == LEFT)
						{
							setRunning();
							AudioManager::getAudioManager()->Play("e_touch_tirtle");
							oPosX = obj->getPosX() + obj->getSizeWidth() + 1;
							oVx = 0.4f; //running with hight speed
							if (oDirect < 0)
							{
								oDirect *= -1;
							}
						}else
							if (isStaticing && directCollision == RIGHT)
							{
								setRunning();
								AudioManager::getAudioManager()->Play("e_touch_tirtle");
								oPosX = obj->getPosX() - getSizeWidth() - 1;
								oVx = -0.4f; //running with hight speed
								if (oDirect > 0)
								{
									oDirect *= -1;
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

					InGameController::getInGameController()->SCORE += 200;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 200);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
					AudioManager::getAudioManager()->Play("e_death_shot");
				}
			}
			break;
		}
	}
	directCollision = NONE;
}

void Turtle::ProcessCollision(MyObject* obj){
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
		directCollision = NONE;
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
					if ((isNormaling || isRunning) && directCollision == TOP)
					{
						if (isNormaling)
						{
							InGameController::getInGameController()->SCORE += 100;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 100);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_mush_die");
						}

						setStaticing();
						oVx = 0;
						setSize(50,50);
						iDynamicSprite.setSize(46,46);
					}else
					if (isStaticing && directCollision == LEFT)
					{
						setRunning();
						AudioManager::getAudioManager()->Play("e_touch_tirtle");
						oPosX = obj->getPosX() + obj->getSizeWidth() + 1;
						oVx = 0.4f; //running with hight speed
						if (oDirect < 0)
						{
							oDirect *= -1;
						}
					}else
					if (isStaticing && directCollision == RIGHT)
					{
						setRunning();
						AudioManager::getAudioManager()->Play("e_touch_tirtle");
						oPosX = obj->getPosX() - getSizeWidth() - 1;
						oVx = -0.4f; //running with hight speed
						if (oDirect > 0)
						{
							oDirect *= -1;
						}
					}
				}
			}
			break;
		case PIPE:
		case LAND_BASE:
		case BRICK_BREAK:
		case BRICK_HARD:
		case QUESTION_BRICK:
			if (oSTT == ACTIVE)
			{
				if (obj->getSTT() == ACTIVE)
				{
					switch(directCollision){
					case BOTTOM:
						if (obj->getVY() != 0) // brick break
						{
							//death with jump up
							oVy = 0.4f;
							oSTT = BEFORE_DEATH;

							InGameController::getInGameController()->SCORE += 200;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 200);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_death_shot");
						}else{
							oPosY += collisionTime * oVy*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() -
								oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();//obj->getPosY() + sizeHeight + 0.6f;
							oVy = 0;
						}
						break;
					case LEFT:
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						if (oDirect < 0)
						{
							oDirect *= -1;
						}
						break;
					case RIGHT:
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						if (oDirect > 0)
						{
							oDirect *= -1;
						}
						break;
					case BOTTOM_LEFT:
					case BOTTOM_RIGHT:
						oPosY -= oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						oVy = 0;
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						break;
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
						if (isStaticing || isNormaling)
						{
							//death with jump up
							oVy = 0.4f;
							oSTT = BEFORE_DEATH;

							InGameController::getInGameController()->SCORE += 200;
							EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 200);
							ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
							AudioManager::getAudioManager()->Play("e_death_shot");
						}
						//if both of them running then they through out together
					}
					else
					{
						if (!isRunning)
						{
							if (directCollision == LEFT)
							{
								if (oDirect > 0)
								{
									oDirect *= -1;
								}
								oPosX = obj->getPosX() + obj->getSizeWidth();
							}
							else if (directCollision == RIGHT)
							{
								if (oDirect > 0)
								{
									oDirect *= -1;
								}
								oPosX = obj->getPosX() - sizeWidth;
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

					InGameController::getInGameController()->SCORE += 200;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 200);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
					AudioManager::getAudioManager()->Play("e_death_shot");
				}
			}
			break;
		}
	}
}

void Turtle::UpdateAnimation(float deltaTime){
	switch(oSTT){
	case ACTIVE:
		if (isNormaling)
		{
			timeAnimate += deltaTime;
			if (timeAnimate > 200)
			{
				timeAnimate = 0;
				iDynamicSprite.AnimateNextFrame(0, 2);
			}
		}
		else if (isStaticing)
		{
			iDynamicSprite.setCurFrame(3);
		}
		else if (isRunning)
		{
			timeAnimate += deltaTime;
			if (timeAnimate > 200)
			{
				timeAnimate = 0;
				iDynamicSprite.AnimateNextFrame(2, 3);
			}
		}
		break;
	}
}

void Turtle::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;

	if (oSTT == ACTIVE || oSTT == BEFORE_DEATH)
	{
		if (isNormaling)
		{
			oVx =  oDirect* g_VX_MUSHROOM_BAD;
		}else if (isRunning)
		{
			oVx =  oDirect* 0.4f;
		}


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

void Turtle::UpdateStatus(float deltaTime){
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

void Turtle::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);

}

void Turtle::UpdateViewPosBeforeDraw(float interpolation){

}

void Turtle::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	switch(oSTT){
	case ACTIVE:
		if (isNormaling)
		{
			iDynamicSprite.setXY(oPosX, oPosY);
			iDynamicSprite.setScaleXY(oDirect, 1);
			dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
		}
		else if (isStaticing || isRunning)
		{
			iDynamicSprite.setXY(oPosX, oPosY);
			iDynamicSprite.setScaleXY(1, 1);
			dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
		}
		break;
	case BEFORE_DEATH:
		iDynamicSprite.setXY(oPosX, oPosY);
		iDynamicSprite.setScaleXY(1, -1);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
		break;
	}
}

void Turtle::Realease(){
	DynamicObject::Realease();
}