#pragma once
#include "StaticObject.h"

class Winpole: public StaticObject{
protected:
public:
	Winpole(void);
	~Winpole(void);

	void Init();
	void ProcessCollision(MyObject* obj){}

	void UpdateAnimation(float deltaTime){}
	void UpdateStatus(float deltaTime){}
	void Update(float deltaTime){}

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};