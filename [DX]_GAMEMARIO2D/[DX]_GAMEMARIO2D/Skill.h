#pragma once
#include "DynamicObject.h"

class Skill: public DynamicObject{
protected:

public:
	Skill(void);
	Skill(float x, float y);
	~Skill(void);
	Skill(Skill* obj);

	virtual void Init(){}

	virtual void ProcessCollision(MyObject* obj){}

	virtual void UpdateAnimation(float deltaTime){}
	virtual void UpdateStatus(float deltaTime){}
	virtual void UpdateMove(float deltaTime){}

	virtual void Update(float deltaTime){}

	virtual void UpdateViewPosBeforeDraw(float interpolation){}

	virtual void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){}
	virtual void Realease();
};