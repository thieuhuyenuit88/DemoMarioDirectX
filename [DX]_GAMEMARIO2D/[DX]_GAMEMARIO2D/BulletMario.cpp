#include "BulletMario.h"
#include "RSMainGame.h"
#include "CollisionDetect.h"

BulletMario::BulletMario(void): Skill(){
	Init();
}

BulletMario::BulletMario(float x, float y):Skill(x, y)
{
	Init();
}

BulletMario::BulletMario(BulletMario* obj):Skill(obj){

}

BulletMario::~BulletMario(void){

}

void BulletMario::Init(){
	dynamicSprite = RSMainGame::getRSMainGame()->getBulletMarioSprite();
	iDynamicSprite.setSize(34,34);
	iDynamicSprite.setDepth(0.1f);

	oID = BULLET_MARIO;
	oAccelY = -0.001f;
	oVx = 0.6f;
	oSTT = ACTIVE;
	setSize(26,26);
}

void BulletMario::ProcessCollision(MyObject* obj){
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
	} 
	//directCollision = DirectionCollision(obj);
	if (directCollision!= NONE)
	{
		switch(obj->getID())
		{
		case BRICK_BREAK:
		case BRICK_HARD:
		case PIPE:
		case LAND_BASE:
		case QUESTION_BRICK:
			if (oSTT == ACTIVE)
			{
				if (obj->getSTT() == ACTIVE)
				{
					if (directCollision == BOTTOM)
					{
						oPosY += collisionTime * oVy*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() -
							oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();//obj->getPosY() + sizeHeight + 0.6f;
						oVy = 0.25f;
					}else{
						oSTT = BEFORE_DEATH;
					}
				}
			}
			break;
		case MUSHROOM_BAD:
		case TURTLE:
		case BOSS:
			if (oSTT == ACTIVE)
			{
				if (obj->getSTT() == ACTIVE)
				{
					oSTT = BEFORE_DEATH;
				}
			}
			break;
		}
	}
}

void BulletMario::UpdateAnimation(float deltaTime){
	switch(oSTT){
	case ACTIVE:
		timeAnimate += deltaTime;
		if (timeAnimate > 100)
		{
			timeAnimate = 0;
			iDynamicSprite.AnimateNextFrame(0, 4);
		}
		break;
	case BEFORE_DEATH:
		timeAnimate += deltaTime;
		if (timeAnimate > 100)
		{
			timeAnimate = 0;
			iDynamicSprite.AnimateNextFrame(4, 6);
		}
		break;
	}
}

void BulletMario::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
	if (oSTT == BEFORE_DEATH)
	{
		timeUpdate += deltaTime;
		if (timeUpdate > 200)
		{
			timeUpdate = 0;
			oSTT = DEATH;
		}
	}
}

void BulletMario::UpdateMove(float deltaTime){
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

void BulletMario::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}


void BulletMario::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	if (oSTT == ACTIVE || oSTT == BEFORE_DEATH)
	{
		iDynamicSprite.setXY(oPosX, oPosY);
		iDynamicSprite.setScaleXY(oDirect, 1);
		dynamicSprite->Draw(spriteHandler, matrixWorld, iDynamicSprite);
	}
}

void BulletMario::Realease(){
	Skill::Realease();
}
