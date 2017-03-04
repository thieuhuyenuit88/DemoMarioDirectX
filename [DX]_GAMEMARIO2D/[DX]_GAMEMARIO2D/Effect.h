#pragma once
#include "MyObject.h"

class Effect: public MyObject{
protected:
	float timeEffect;
public:
	Effect(void);
	Effect(float x, float y);
	~Effect(void);

	virtual void Init(){}

	void ProcessCollision(MyObject* obj){} //do nothing :)

	virtual void UpdateAnimation(float deltaTime){}
	virtual void UpdateStatus(float deltaTime){}
	virtual void UpdateMove(float deltaTime){}

	virtual void Update(float deltaTime){}

	virtual void UpdateViewPosBeforeDraw(float interpolation){}

	virtual void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){}
	virtual void Realease(){}
};