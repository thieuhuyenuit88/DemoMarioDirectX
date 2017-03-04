#pragma once
#include "MyObject.h"
#include "Sprite.h"

class DynamicObject: public MyObject{
protected:
	Sprite* dynamicSprite;
	ISprite iDynamicSprite;

	float nextPosX, nextPosY;
	float nextVx, nextVy;

	float prevPosX, prevPosY;
public:
	DynamicObject(void);
	virtual ~DynamicObject(void);
	DynamicObject(DynamicObject* obj);

	int directCollision;

	Sprite* getDynamicSprite(){
		return dynamicSprite;
	}

	ISprite getISprite(){
		return iDynamicSprite;
	}

	float getPrevPosX(){
		return prevPosX;
	}

	float getPrevPosY(){
		return prevPosY;
	}
	CRECT getNextRect(){
		CRECT rect;
		rect.top = nextPosY;
		rect.bottom = nextPosY - sizeHeight;
		rect.left = nextPosX;
		rect.right = nextPosX + sizeWidth;
		return rect;
	}

	CRECT getPrevRect(){
		CRECT rect;
		rect.top = prevPosY;
		rect.bottom = prevPosY - sizeHeight;
		rect.left = prevPosX;
		rect.right = prevPosX + sizeWidth;
		return rect;
	}

	virtual bool isCollision(MyObject* obj);

	virtual void Init(){}
	virtual void ProcessCollision(MyObject* obj){}

	virtual void ProcessCollision(MyObject* obj, int _dir){}

	virtual void UpdateAnimation(float deltaTime){}
	virtual void UpdateStatus(float deltaTime){}
	virtual void UpdateMove(float deltaTime);
	virtual void Update(float deltaTime);

	virtual void UpdateViewPosBeforeDraw(float interpolation);

	virtual void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	virtual void Realease();

};