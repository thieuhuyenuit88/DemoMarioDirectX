#include "Mario.h"
#include "RSMainGame.h"
#include "DXDeviceManager.h"
#include "CLog.h"
#include "CRandom.h"
#include "Turtle.h"
#include "BulletMario.h"
#include "Mushroom.h"
#include "Flower.h"
#include "ManagerObject.h"
#include "AudioManager.h"
#include "InGameController.h"
#include "CollisionDetect.h"

Mario::Mario(void): DynamicObject(){
	setNomaling();
	Init();
}

Mario::~Mario(void){

}

Mario::Mario(Mario* obj):DynamicObject(obj){
	isNomaling = obj->isNomaling;
	isInving = obj->isInving;
	isUpping = obj->isUpping;
	isDowning = obj->isDowning;
	isShotting = obj->isShotting;
	isWinning = obj->isWinning;
}

void Mario::setID(int _id){
	oID = _id;
	if (oID == MARIO_SUPER)
	{
		marioSprite = RSMainGame::getRSMainGame()->getMarioSuperSprite();
		iSpriteMario.setSize(50,100);
		setSize(48, 98);
	}else if (oID == MARIO_BIG)
	{
		marioSprite = RSMainGame::getRSMainGame()->getMarioBigSprite();
		iSpriteMario.setSize(50,100);
		setSize(48, 98);
	}else if (oID == MARIO)
	{
		marioSprite = RSMainGame::getRSMainGame()->getMarioSmallSprite();
		iSpriteMario.setSize(50,50);
		setSize(48, 48);
	}
}

void Mario::Init(){
	marioSprite = RSMainGame::getRSMainGame()->getMarioSuperSprite();
	iSpriteMario.setSize(50,100);
	iSpriteMario.setDepth(0.02f);

	oID = MARIO_SUPER;
	isJump = false;
	scaleX = scaleY = 1;
	colorA = 1;
	oDirect = 1;
	oAccelY = g_ACCELY;
	oSTT = ACTIVE;
	setSize(48, 98);
}

void Mario::ProcessCollisionOld(MyObject* obj){
	directCollision = NONE;
	directCollision = DirectionCollision(obj);
	if(directCollision != NONE){
		switch(obj->getID()){
		case PIPE:
		case LAND_BASE:
		case BRICK_BREAK:
		case BRICK_HARD:
		case QUESTION_BRICK:
			if (oSTT == ACTIVE && obj->getSTT() == ACTIVE)
			{
				switch(directCollision){
				case TOP:
					oVy = 0;
					oPosY = obj->getPosY() - obj->getSizeHeight();
					break;
				case BOTTOM:
					oVy = 0;
					isJump = true;
					oPosY = obj->getPosY() + sizeHeight + 0.6f;
					break;
				case LEFT:
					if (oVx < 0)
					{
						oVx = 0;
					}
					oPosX = obj->getPosX() + obj->getSizeWidth();
					break;
				case RIGHT:
					if (oVx > 0)
					{
						oVx = 0;
					}
					oPosX = obj->getPosX() - sizeWidth;
					break;
				}
			}
			break;
		}
	}
}

void Mario::ProcessCollision(MyObject* obj){
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
		//ProcessCollisionOld(obj);
		directCollision = NONE;
		directCollision = DirectionCollision(obj);
	}
	//directCollision = DirectionCollision(obj);
	if(directCollision != NONE){
		switch(obj->getID()){
		case PIPE:
		case LAND_BASE:
		case BRICK_BREAK:
		case BRICK_HARD:
		case QUESTION_BRICK:
			if (oSTT == ACTIVE && obj->getSTT() == ACTIVE)
			{
				switch(directCollision){
				case TOP:
					//don't need
					oPosY += collisionTime * oVy*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
					oVy = 0;
					break;
				case BOTTOM:
					//need process good!
					isJump = true;
					oPosY += collisionTime * oVy*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() -
						oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();//obj->getPosY() + sizeHeight + 0.6f;
					oVy = 0;
					break;
				case LEFT:
					//need process good!
					oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() + DXDeviceManager::getInstanceDXDevice()->getDeltaTime()*g_MAX_VX_SMALL;
					if (oVx < 0)
					{
						oVx = 0;
					}
					break;
				case RIGHT:
					//need process good!
					oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() - DXDeviceManager::getInstanceDXDevice()->getDeltaTime()*g_MAX_VX_SMALL;
					if (oVx > 0)
					{
						oVx = 0;
					}
					break;
				case BOTTOM_LEFT:
					//need process good!
					isJump = true;
					oPosY -= oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
					oVy = 0;
					oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
					break;
				case BOTTOM_RIGHT:
					//need process good!
					isJump = true;
					oPosY -= oAccelY*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() * DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
					oVy = 0;
					oPosX += collisionTime * oVx*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
					break;
				}
			}
			break;
		case MUSHROOM_BAD:
			if (oSTT == ACTIVE)
			{
				if (obj->getSTT() == ACTIVE)
				{
					switch(directCollision){
					case BOTTOM:
						/*if (isNomaling || isShotting)
						{*/
							//restitution jump up
							oVy = g_VY_RESTITUTION;
							oPosY = obj->getPosY() + sizeHeight + 2;
						//}
						break;
					case LEFT:
					case RIGHT:
						if (!isInving && !isDowning && !isUpping && !isWinning)
						{
							if (oID == MARIO)
							{
								//Die with jump up sky
								oVx = 0.0f;
								oVy = 0.9f;
								oSTT = BEFORE_DEATH;
								InGameController::getInGameController()->LIFE -= 1;
								AudioManager::getAudioManager()->Play("e_death");
							}else
							if (oID == MARIO_BIG)
							{
								oID = MARIO;
								marioSprite = RSMainGame::getRSMainGame()->getMarioSmallSprite();
								iSpriteMario.setSize(50,50);
								setSize(48,48);
								//be short :)
								oPosY -= 50;

								setDowning();
								AudioManager::getAudioManager()->Play("e_grow");
							}else
							if (oID == MARIO_SUPER)
							{
								marioSprite = RSMainGame::getRSMainGame()->getMarioBigSprite();
								oID = MARIO_BIG;

								setInving();
								AudioManager::getAudioManager()->Play("e_grow");
							}
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
					switch(directCollision){
					case BOTTOM:
						oVy = g_VY_RESTITUTION;
						oPosY = obj->getPosY() + sizeHeight + 2;
						break;
					case LEFT:
					case RIGHT:
						if (!isInving && !isDowning && !isUpping && !isWinning)
						{
							if (((Turtle*)obj)->isNormaling || ((Turtle*)obj)->isRunning)
							{
								if (oID == MARIO)
								{
									//Die with jump up sky
									oVx = 0.0f;
									oVy = 0.9f;
									oSTT = BEFORE_DEATH;
									InGameController::getInGameController()->LIFE -= 1;
									AudioManager::getAudioManager()->Play("e_death");
								}else
								if (oID == MARIO_BIG)
								{
									oID = MARIO;
									marioSprite = RSMainGame::getRSMainGame()->getMarioSmallSprite();
									iSpriteMario.setSize(50,50);
									setSize(48,48);
									//be short :)
									oPosY -= 50;

									setDowning();
									AudioManager::getAudioManager()->Play("e_grow");
								}else
								if (oID == MARIO_SUPER)
								{
									marioSprite = RSMainGame::getRSMainGame()->getMarioBigSprite();
									oID = MARIO_BIG;

									setInving();
									AudioManager::getAudioManager()->Play("e_grow");
								}
							}
						}
						break;
					}
				}
			}
			break;
		case MUSHROOMBIG:
			if (oID == MARIO)
			{
				if (obj->getSTT() ==  ACTIVE && !((Mushroom*)obj)->isUpping)
				{
					if (oSTT == ACTIVE && (isNomaling || isShotting))
					{
						setUpping();
						AudioManager::getAudioManager()->Play("e_grow");
					}
				}
			}
			break;
		case FLOWER:
			if (obj->getSTT() ==  ACTIVE && !((Flower*)obj)->isUpping)
			{
				switch(oID){
				case MARIO:
					if (oSTT == ACTIVE && isNomaling)
					{
						setUpping();
						AudioManager::getAudioManager()->Play("e_grow");
					}
					break;
				case MARIO_BIG:
					if (oSTT == ACTIVE && isNomaling)
					{
						setInving();
						AudioManager::getAudioManager()->Play("e_grow");

						marioSprite = RSMainGame::getRSMainGame()->getMarioSuperSprite();
						oID = MARIO_SUPER;
					}
					break;
				}
				
			}
			break;
		case BOSS:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE)
				{
					switch(directCollision){
					case BOTTOM:
						//restitution with jump up
						oVy = g_VY_RESTITUTION;
						oPosY = obj->getPosY() + sizeHeight + 2;
						break;
					case RIGHT:
					case LEFT:
						if (!isInving && !isDowning && !isUpping && !isWinning)
						{
							if (oID == MARIO)
							{
								//Die with jump up sky
								oVx = 0.0f;
								oVy = 0.9f;
								oSTT = BEFORE_DEATH;
								AudioManager::getAudioManager()->Play("e_death");
								InGameController::getInGameController()->LIFE -= 1;
							}else
							if (oID == MARIO_BIG)
							{
								oID = MARIO;
								marioSprite = RSMainGame::getRSMainGame()->getMarioSmallSprite();
								iSpriteMario.setSize(50,50);
								setSize(48,48);
								//be short :)
								oPosY -= 50;

								setDowning();
								AudioManager::getAudioManager()->Play("e_grow");
							}else
							if (oID == MARIO_SUPER)
							{
								marioSprite = RSMainGame::getRSMainGame()->getMarioBigSprite();
								oID = MARIO_BIG;

								setInving();
								AudioManager::getAudioManager()->Play("e_grow");
							}
						}
						break;
					}
				}
			}
			break;
		case BULLET_BOSS:
			if (obj->getSTT() == ACTIVE)
			{
				if (oSTT == ACTIVE)
				{
					if (isNomaling || isShotting)
					{
						if (oID == MARIO)
						{
							//Die with jump up sky
							oVx = 0.0f;
							oVy = 0.9f;
							oSTT = BEFORE_DEATH;
							AudioManager::getAudioManager()->Play("e_death");
						}else
						if (oID == MARIO_BIG)
						{
							oID = MARIO;
							marioSprite = RSMainGame::getRSMainGame()->getMarioSmallSprite();
							iSpriteMario.setSize(50,50);
							setSize(48,48);
							//be short :)
							oPosY -= 50;

							setDowning();
							AudioManager::getAudioManager()->Play("e_grow");
						}else
						if (oID == MARIO_SUPER)
						{
							marioSprite = RSMainGame::getRSMainGame()->getMarioBigSprite();
							oID = MARIO_BIG;

							setInving();
							AudioManager::getAudioManager()->Play("e_grow");
						}
					}
				}
			}
			break;
		}
		//Clog::getClogInstance()->outLog("PosX %f PosY %f", oPosX, oPosY);
	}
}

void Mario::UpdateAnimation(float deltaTime){
	switch(oSTT){
	case ACTIVE:
		if (isNomaling || isInving || isWinning)
		{
			if (oVx!=0)
			{
				if (oDirect * oVx < 0)
				{
					iSpriteMario.setCurFrame(4);
				}else{
					timeAnimate += deltaTime;
					if (timeAnimate >= 100)
					{
						timeAnimate = 0;
						iSpriteMario.setCurFrame((iSpriteMario.getCurFrame() + 1) % 3);
					}
				}
			}else
			{
				iSpriteMario.setCurFrame(0);
			}
			//jumping
			if (oVy !=0 )
			{
				iSpriteMario.setCurFrame(3);
			}

			if (isInving)
			{
				colorA = (float)(CRandom::RandomBetweenIntRemoveBias(0, 255)) / 255.0f;
			}
		}
		else if (isShotting)
		{
			iSpriteMario.setCurFrame(2);
		}
		else if (isUpping || isDowning)
		{
			iSpriteMario.setCurFrame(0);
			scaleX = (float)(CRandom::RandomBetweenIntRemoveBias(100,200))/ 100.0f;
			scaleY = (float)(CRandom::RandomBetweenIntRemoveBias(100,200))/ 100.0f;
			colorA = (float)(CRandom::RandomBetweenIntRemoveBias(0, 255)) / 255.0f;
			//Clog::getClogInstance()->outLog("%f %f %f", scaleX, scaleY, colorA);
		}
		break;
	case BEFORE_DEATH:
		iSpriteMario.setCurFrame(5);
		break;
	}
}

void Mario::UpdateMove(float deltaTime){
	
	prevPosX = oPosX;
	prevPosY = oPosY;

	switch(oSTT){
	case ACTIVE:
		if (isNomaling || isShotting || isUpping || isDowning || isInving)
		{
			oVx += oAccelX * deltaTime;
			oVy += oAccelY * deltaTime;
			//if not press move - stop slowdown
			if (oAccelX == 0)
			{
				if (oVx!=0)
				{
					//direction to right
					if (oVx>0)
					{
						oVx -= g_FRICTION;
						if (oVx < 0)
						{
							oVx = 0;
						}
					}
					//direction to left
					else{
						oVx += g_FRICTION;
						if (oVx > 0)
						{
							oVx = 0;
						}
					}
				}
			}

			//Limit velloc x
			if (oID == MARIO)
			{
				if (fabs(oVx) > g_MAX_VX_SMALL)
				{
					if (oVx < 0)
					{
						oVx = -g_MAX_VX_SMALL;
					}
					else{
						oVx = g_MAX_VX_SMALL;
					}
				}
			}else if (oID == MARIO_BIG || oID == MARIO_SUPER)
			{
				if (fabs(oVx) > g_MAX_VX_BIG)
				{
					if (oVx < 0)
					{
						oVx = -g_MAX_VX_BIG;
					}
					else{
						oVx = g_MAX_VX_BIG;
					}
				}
			}
			

			oPosX += oVx*deltaTime;
			oPosY += oVy*deltaTime;

			//Calculate next position in next frame
			nextVx = oVx + oAccelX*deltaTime;
			nextVy = oVy + oAccelY*deltaTime;
			nextPosX = oPosX + oVx*deltaTime;
			nextPosY = oPosY + oVy*deltaTime;
			
			//limit position - check by position in next frame
			if (oPosX < 0 && prevPosX >= 0)
			{
				oPosX = 0;
				oVx = 0;
			}
			/*else if (nextPosX <= 0)
			{
				oPosX = 0;
				oVx = 0;
			}*/

			//fall 
			if (oPosY < 0 && prevPosY <= 0)
			{
				//Die with jump up sky
				if (oID == MARIO_BIG || oID == MARIO_SUPER)
				{
					oID = MARIO;
					marioSprite = RSMainGame::getRSMainGame()->getMarioSmallSprite();
					iSpriteMario.setSize(50,50);
					setSize(50,50);
					//be short :)
				}
				oVx = 0.0f;
				oVy = 1.5f;
				oSTT = BEFORE_DEATH;
				InGameController::getInGameController()->LIFE -= 1;
				AudioManager::getAudioManager()->Play("e_death");
			}
			/*else if (nextPosY >= g_SCREEN_HEIGHT - sizeHeight)
			{
				oPosY = g_SCREEN_HEIGHT - sizeHeight;
				oVy = 0;
				isJump = true;
			}*/
			//reset accel
			oAccelX = 0;
		}else if (isWinning)
		{
			setVX(0.15f);

			oVx += oAccelX * deltaTime;
			oVy += oAccelY * deltaTime;
			oPosX += oVx*deltaTime;
			oPosY += oVy*deltaTime;
		}
		break;
	case BEFORE_DEATH:
		oVx += oAccelX * deltaTime;
		oVy += oAccelY * deltaTime;
		oPosX += oVx*deltaTime;
		oPosY += oVy*deltaTime;
		break;
	}
}

void Mario::UpdateStatus(float deltaTime){
	oOldSTT = oSTT;
	switch(oSTT){
	case ACTIVE:
		if (isDowning)
		{
			timeUpdate += deltaTime;
			if (timeUpdate > 500)
			{
				timeUpdate = 0;
				setInving();
			}
		}else if (isInving)
		{
			timeUpdate += deltaTime;
			if (timeUpdate > 1000)
			{
				timeUpdate = 0;
				setNomaling();
			}
		}else if (isUpping)
		{
			timeUpdate += deltaTime;
			if (timeUpdate > 500)
			{
				timeUpdate = 0;

				oID = MARIO_BIG;
				marioSprite = RSMainGame::getRSMainGame()->getMarioBigSprite();
				iSpriteMario.setSize(50,100);
				setSize(48, 98);
				oPosY += 50;

				setInving();
			}
		}else if (isShotting)
		{
			timeUpdate += deltaTime;
			if (timeUpdate > 100)
			{
				timeUpdate = 0;
				setNomaling();
			}
		}
		break;
	case BEFORE_DEATH:
		timeUpdate += deltaTime;
		if (timeUpdate > 3000)
		{
			timeUpdate = 0;
			oSTT = DEATH;
		}
		break;

	}
}

void Mario::Update(float deltaTime){
	UpdateAnimation(deltaTime);
	UpdateMove(deltaTime);
	UpdateStatus(deltaTime);
}

void Mario::UpdateViewPosBeforeDraw(float interpolation){

}

void Mario::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	
	iSpriteMario.setXY(oPosX, oPosY);
	
	switch(oSTT){
	case ACTIVE:
		if (isNomaling || isShotting || isWinning)
		{
			iSpriteMario.setScaleX(oDirect);
			marioSprite->Draw(spriteHandler, matrixWorld, iSpriteMario);
		}
		else if (isUpping || isDowning)
		{
			iSpriteMario.setScaleXY(oDirect * scaleX, scaleY);
			iSpriteMario.setColorAlpha(colorA);
			marioSprite->Draw(spriteHandler, matrixWorld, iSpriteMario);
			iSpriteMario.setScaleXY(oDirect, 1);
			iSpriteMario.setColorAlpha(1);
		}
		else if (isInving)
		{
			iSpriteMario.setScaleX(oDirect);
			iSpriteMario.setColorAlpha(colorA);
			marioSprite->Draw(spriteHandler, matrixWorld, iSpriteMario);
			iSpriteMario.setColorAlpha(1);
		}
		break;
	case BEFORE_DEATH:
		iSpriteMario.setScaleX(oDirect);
		marioSprite->Draw(spriteHandler, matrixWorld, iSpriteMario);
		break;
	}
	
}

void Mario::Realease(){
	DynamicObject::Realease();
	marioSprite->Realease();
	delete marioSprite;
	marioSprite = NULL;
}

void Mario::setJump(){
	if (oVy == 0 && isJump)
	{
		isJump = false;
		AudioManager::getAudioManager()->Play("e_jump");
		if (oID == MARIO)
		{
			oVy = g_VY_JUMP_SMALL;
		}else if (oID == MARIO_BIG || MARIO_SUPER)
		{
			oVy = g_VY_JUMP_BIG;
		}
		
		if (oVx != 0)
		{
			if (oVx>0)
			{
				oVy = oVy + oVx*g_VY_JUMP_ADD;
			}else{
				oVy = oVy - oVx*g_VY_JUMP_ADD;
			}	
		}
		
	}
}

void Mario::setShot(){
	if (oID == MARIO_SUPER)
	{
		AudioManager::getAudioManager()->Play("e_shot");
		BulletMario* bulletMario;
		if (oDirect>0)
		{
			bulletMario = new BulletMario(oPosX + 40, oPosY - 40);
			bulletMario->setDirect(oDirect);
		}else
		if (oDirect < 0)
		{
			bulletMario = new BulletMario(oPosX, oPosY - 40);
			bulletMario->setDirect(oDirect);
		}

		setShotting();
		ManagerObject::getManagerObject()->getListSkill()->push_back(bulletMario);
	}
}

