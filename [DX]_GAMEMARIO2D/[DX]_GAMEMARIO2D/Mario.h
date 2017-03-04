#pragma once
#include "DynamicObject.h"

class Mario: public DynamicObject{
protected:
	Sprite* marioSprite;
	ISprite iSpriteMario;

	float scaleX;
	float scaleY;
	float colorA;
	bool isJump;
public:
	Mario(void);
	~Mario(void);
	Mario(Mario* obj);

	void setID(int _id);

	void setMarioSprite(Sprite* _sprite){
		marioSprite = _sprite;
	}

	Sprite* getMarioSprite(){
		return marioSprite;
	}

	ISprite getISpriteMario(){
		return iSpriteMario;
	}

	bool isNomaling;
	bool isInving;
	bool isUpping;
	bool isDowning;
	bool isShotting;
	bool isWinning;

	void setNomaling(){
		isNomaling = true;
		isInving = isUpping = isDowning = isShotting = isWinning = false;
	}

	void setInving(){
		isInving = true;
		isNomaling = isUpping = isDowning = isShotting = isWinning = false;
	}

	void setUpping(){
		isUpping = true;
		isNomaling = isInving = isDowning = isShotting = isWinning = false;
	}

	void setDowning(){
		isDowning = true;
		isNomaling = isInving = isUpping = isShotting = isWinning = false;
	}

	void setShotting(){
		isShotting = true;
		isNomaling = isInving = isUpping = isDowning = isWinning = false;
	}

	void setWinning(){
		isWinning = true;
		isNomaling = isInving = isUpping = isDowning = isShotting = false;
	}


	ISprite getISprite(){
		return iSpriteMario;
	}

	void setStopMove(){
		oAccelX = 0;
	}

	void setMoveRight(){
		if (oSTT == ACTIVE)
		{
			oDirect = 1;
			oAccelX = g_ACCELX;
		}
	}

	void setMoveLeft(){
		if (oSTT == ACTIVE)
		{
			oDirect = -1;
			oAccelX = -g_ACCELX;
		}
	}

	void setJump();
	void setShot();

	//int DirectionCollision(MyObject* obj);

	void Init();
	void ProcessCollision(MyObject* obj);
	void ProcessCollisionOld(MyObject* obj);

	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation);
	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};