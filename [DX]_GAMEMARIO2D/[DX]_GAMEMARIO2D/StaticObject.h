#pragma once
#include "MyObject.h"
#include "Sprite.h"

class StaticObject: public MyObject{
protected:
	Sprite* staticSprite;
	ISprite iStaticSprite;
public:
	StaticObject(void);
	virtual ~StaticObject(void);
	StaticObject(StaticObject* obj);

	Sprite* getStaticSprite(){
		return staticSprite;
	}

	ISprite getISprite(){
		return iStaticSprite;
	}

	virtual void Init(){}
	virtual void ProcessCollision(MyObject* obj){}
	
	virtual void UpdateAnimation(float deltaTime){}
	virtual void UpdateStatus(float deltaTime){}
	virtual void Update(float deltaTime);

	virtual void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	virtual void Realease();
};