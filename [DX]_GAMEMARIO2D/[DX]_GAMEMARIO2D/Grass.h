#pragma once
#include "StaticObject.h"

class Grass: public StaticObject{
protected:
public:
	Grass(void);
	~Grass(void);

	void Init();
	void ProcessCollision(MyObject* obj){}

	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime){}
	void Update(float deltaTime);

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};