#include "Mushroom.h"
#include "RSMainGame.h"
#include "EffectRenderScore.h"
#include "ManagerObject.h"
#include "InGameController.h"
#include "AudioManager.h"
#include "CollisionDetect.h"

Mushroom::Mushroom(void):DynamicObject(){
	Init();
}

Mushroom::~Mushroom(void){
	
}

Mushroom::Mushroom(Mushroom* obj):DynamicObject(obj){
	startPosY = obj->getStartPosY();
}

void Mushroom::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getMushroomSprite();
	iDynamicSprite.setSize(50,50);
	iDynamicSprite.setDepth(0.2f);

	setSize(48,48);
	oSTT = READY;
	isNormaling = isUpping = false;
}

void Mushroom::ProcessCollision(MyObject* obj, int _dir){
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
				if (oSTT == ACTIVE && !isUpping)
				{
					InGameController::getInGameController()->SCORE += 500;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 500);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);

					if (oID == MUSHROOMUP)
					{
						InGameController::getInGameController()->LIFE += 1;
						AudioManager::getAudioManager()->Play("e_1up");
					}
					oSTT = DEATH;
				}
			}
			break;
		}
	}
	directCollision = NONE;
}

void Mushroom::ProcessCollision(MyObject* obj){

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
				if (oSTT == ACTIVE && !isUpping)
				{
					InGameController::getInGameController()->SCORE += 500;
					EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)oPosX, (int)oPosY, 500);
					ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);

					if (oID == MUSHROOMUP)
					{
						InGameController::getInGameController()->LIFE += 1;
						AudioManager::getAudioManager()->Play("e_1up");
					}
					oSTT = DEATH;
				}
			}
			break;
		case PIPE:
		case LAND_BASE:
		case BRICK_BREAK:
		case BRICK_HARD:
		case QUESTION_BRICK:
			if (oSTT == ACTIVE && !isUpping)
			{
				if (obj->getSTT() == ACTIVE)
				{
					if (directCollision == BOTTOM)
					{
						oPosY += collisionTime * oVy*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() -
							oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();//obj->getPosY() + sizeHeight + 0.6f;
						oVy = 0;
					}else
					if (directCollision == LEFT)
					{
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						if (oDirect < 0)
						{
							oDirect *= -1;
						}
					}else
					if (directCollision == RIGHT)
					{
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						if (oDirect > 0)
						{
							oDirect *= -1;
						}
					}else 
					if (directCollision == BOTTOM_LEFT || directCollision == BOTTOM_RIGHT)
					{
						oPosY -= oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						oVy = 0;
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
					}
				}
			}
			break;
		}
	}
}

void Mushroom::UpdateAnimation(float deltaTime){
	switch (oSTT)
	{
	case ACTIVE:
		if (oID == MUSHROOMBIG)
		{
			iDynamicSprite.setCurFrame(0);
		}else
		if (oID == MUSHROOMUP)
		{
			iDynamicSprite.setCurFrame(1);
		}
		break;
	}
}

void Mushroom::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;
	switch(oSTT){
	case ACTIVE:
		if (isUpping)
		{
			oPosY += oVy*deltaTime;
		}else if (isNormaling)
		{
			oVx = oDirect * 0.2f;

			oVx += oAccelX*deltaTime;
			oVy += oAccelY*deltaTime;
			oPosX += oVx*deltaTime;
			oPosY += oVy*deltaTime;

			if (oPosY < 0 && prevPosY <= 0)
			{
				oSTT = DEATH;
			}
		}
		break;
	}
}

void Mushroom::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
	switch(oSTT){
	case ACTIVE:
		if (isUpping)
		{
			if (oPosY > startPosY + sizeHeight)
			{
				oPosY = startPosY + sizeHeight;
				oAccelY = -0.001f; // gravity
				oVy = oAccelY * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
				oDirect = 1;
				//oVx = 0.2f; // velocity
				setNormaling();
			}
		}
		break;
	}
}

void Mushroom::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void Mushroom::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	if (oSTT == ACTIVE)
	{
		iDynamicSprite.setXY(oPosX, oPosY);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
	}
}

void Mushroom::Realease(){
	DynamicObject::Realease();
}