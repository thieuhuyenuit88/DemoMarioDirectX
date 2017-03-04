#pragma once
#include "StaticObject.h"

class BrickHard: public StaticObject{
protected:
public:
	BrickHard(void);
	~BrickHard(void);

	void Init();
	void ProcessCollision(MyObject* obj);

	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime);
	void Update(float deltaTime);

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};