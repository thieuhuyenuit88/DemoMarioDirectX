#pragma once
#include "StaticObject.h"

class Building: public StaticObject{
protected:
public:
	Building(void);
	~Building(void);

	void Init();
	void ProcessCollision(MyObject* obj){}

	void UpdateAnimation(float deltaTime){}
	void UpdateStatus(float deltaTime){}
	void Update(float deltaTime){}

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};