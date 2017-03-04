#include "Boss.h"
#include "RSMainGame.h"
#include "CRandom.h"
#include "ManagerObject.h"
#include "BulletBoss.h"
#include "EffectBossExplode.h"
#include "AudioManager.h"
#include "CollisionDetect.h"

Boss::Boss(void): DynamicObject(){
	Init();
}

Boss::Boss(Boss* obj):DynamicObject(obj){
	isNormaling = obj->isNormaling;
	isHurtting = obj->isHurtting;
	isShotting = obj->isShotting;
}

Boss::~Boss(void){

}

void Boss::Init(){
	oID = BOSS;
	oSTT = ACTIVE;

	dynamicSprite = RSMainGame::getRSMainGame()->getBossSprite();
	iDynamicSprite.setSize(100, 110);
	iDynamicSprite.setDepth(0.02f);
	setSize(98, 108);

	blood = 100;
	oAccelY = -0.001f;
	oVy = oAccelY * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
	oDirect = -1;
	scaleX = scaleY = 1.0f; 
	colorA = 1;
	timeChangeMove = timeShot = 0;
	setNormaling();
}

void Boss::ProcessCollision(MyObject* obj, int _dir){
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
				if (oSTT == ACTIVE && (isNormaling || isShotting))
				{
					if (directCollision == TOP)
					{
						blood -= 10;
						AudioManager::getAudioManager()->Play("e_boss_hurt");
						setHurtting();
					}
				}
			}
			break;
		case BULLET_MARIO:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE && (isShotting || isNormaling))
				{
					blood -= 10;
					AudioManager::getAudioManager()->Play("e_boss_hurt");
					setHurtting();
				}
			}
			break;
		}
	}
}

void Boss::ProcessCollision(MyObject* obj){
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
				if (oSTT == ACTIVE && (isNormaling || isShotting))
				{
					if (directCollision == TOP)
					{
						blood -= 10;
						AudioManager::getAudioManager()->Play("e_boss_hurt");
						setHurtting();
					}
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
							if (isNormaling || isShotting)
							{
								blood -= 10;
								AudioManager::getAudioManager()->Play("e_boss_hurt");
								setHurtting();
							}
						}else
						{
							oPosY += collisionTime * oVy*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() -
								oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();//obj->getPosY() + sizeHeight + 0.6f;
							oVy = 0;
						}
					}else
					if (directCollision == BOTTOM_LEFT || directCollision == BOTTOM_RIGHT)
					{
						oPosY -= oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
						oVy = 0;
						oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
					}
					else
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
			break;
		case BULLET_MARIO:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE && (isShotting || isNormaling))
				{
					blood -= 10;
					AudioManager::getAudioManager()->Play("e_boss_hurt");
					setHurtting();
				}
			}
			break;
		}
	}
}

void Boss::UpdateAnimation(float deltaTime){
	switch(oSTT){
	case ACTIVE:
		if (isNormaling)
		{
			timeAnimate += deltaTime;
			if (timeAnimate > 200)
			{
				timeAnimate = 0;
				iDynamicSprite.AnimateNextFrame(0, 3);
			}
		}else
		if (isShotting)
		{
			iDynamicSprite.setCurFrame(0);
		}else
		if (isHurtting)
		{
			iDynamicSprite.setCurFrame(2);
			colorA = (float)(CRandom::RandomBetweenIntRemoveBias(0, 255)) / 255.0f;
		}
		break;
	case BEFORE_DEATH:
		iDynamicSprite.setCurFrame(2);
		scaleX = (float)(CRandom::RandomBetweenIntRemoveBias(100,200))/ 100.0f;
		scaleY = (float)(CRandom::RandomBetweenIntRemoveBias(100,200))/ 100.0f;
		colorA = (float)(CRandom::RandomBetweenIntRemoveBias(0, 255)) / 255.0f;
		break;
	}
}

void Boss::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
	switch(oSTT){
	case ACTIVE:
		if (isShotting)
		{
			timeUpdate += deltaTime;
			if (timeUpdate > 1000)
			{
				timeUpdate = 0;
				setNormaling();
			}
		}else
		if (isNormaling)
		{
			timeUpdate += deltaTime;
			if (timeUpdate > 2000)
			{
				timeUpdate = 0;
				int choose = CRandom::RandomBetweenIntRemoveBias(0, 1);
				if (choose == 0)
				{
					setShotting();
				}
			}
		}else
		if (isHurtting)
		{
			timeUpdate += deltaTime;
			if (timeUpdate > 1000)
			{
				timeUpdate = 0;
				int choose = CRandom::RandomBetweenIntRemoveBias(0, 1);
				if (choose == 0)
				{
					setShotting();
				}else{
					setNormaling();
				}
			}
		}
		if (blood <= 0)
		{
			blood = 0;
			oSTT = BEFORE_DEATH;
			AudioManager::getAudioManager()->Play("e_boss_before_die");
		}
		break;
	case BEFORE_DEATH:
		timeUpdate += deltaTime;
		if (timeUpdate > 1000)
		{
			timeUpdate = 0;
			oSTT = DEATH;

			EffectBossExplode* effBossExplode = new EffectBossExplode(oPosX, oPosY);
			ManagerObject::getManagerObject()->getListEffect()->push_back(effBossExplode);
			AudioManager::getAudioManager()->Play("e_boss_die");
		}
		break;
	}
}

void Boss::UpdateMove(float deltaTime){
	prevPosX = oPosX;
	prevPosY = oPosY;

	switch(oSTT){
	case ACTIVE:
		if (isHurtting || isNormaling)
		{
			oVx = oDirect*0.15f;

			timeChangeMove += deltaTime;
			if (timeChangeMove > 1500)
			{
				timeChangeMove = 0;
				int choose = CRandom::RandomBetweenIntRemoveBias(0, 1);
				if (choose == 0)
				{
					oDirect *= -1;
				}
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
		break;
	}
	directCollision = NONE;
}

void Boss::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
	updateShot(deltaTime);
}

void Boss::UpdateViewPosBeforeDraw(float interpolation){

}

void Boss::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	iDynamicSprite.setXY(oPosX, oPosY);
	switch(oSTT){
	case ACTIVE:
		if (isNormaling || isShotting)
		{
			iDynamicSprite.setScaleX(oDirect);
			dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
		}
		else if (isHurtting)
		{
			iDynamicSprite.setColorAlpha(colorA);
			dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
			iDynamicSprite.setColorAlpha(1);
		}
		break;
	case BEFORE_DEATH:
		iDynamicSprite.setColorAlpha(colorA);
		iDynamicSprite.setScaleXY(scaleX * oDirect, scaleY);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
		iDynamicSprite.setColorAlpha(1);
		iDynamicSprite.setScaleXY(oDirect, 1);
		break;
	}

}

void Boss::Realease(){
	DynamicObject::Realease();
}

void Boss::updateShot(float deltaTime){
	if (isShotting)
	{
		AudioManager::getAudioManager()->Play("e_boss_fire");
		timeShot += deltaTime;
		if (timeShot > 300)
		{
			timeShot = 0;
			BulletBoss* bulletBoss;
			if (oDirect > 0)
			{
				bulletBoss = new BulletBoss(oPosX + 70, oPosY - 20);
				bulletBoss->setDirect(oDirect);
			}else
			if (oDirect < 0)
			{
				bulletBoss = new BulletBoss(oPosX - 20, oPosY - 20);
				bulletBoss->setDirect(oDirect);
			}

			ManagerObject::getManagerObject()->getListSkill()->push_back(bulletBoss);
		}
	}
}