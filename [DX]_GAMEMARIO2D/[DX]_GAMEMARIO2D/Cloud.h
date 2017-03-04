#pragma once
#include "StaticObject.h"

class Cloud: public StaticObject{
protected:
public:
	Cloud(void);
	~Cloud(void);

	void Init();
	void ProcessCollision(MyObject* obj){}

	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime){}
	void Update(float deltaTime);

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};