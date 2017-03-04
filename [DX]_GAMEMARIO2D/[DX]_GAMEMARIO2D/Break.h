#pragma once
#include "DynamicObject.h"

class Break: public DynamicObject{
private:
	int rotationBreak;
public:
	Break(void);
	~Break(void);

	void Init();

	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime);
	void UpdateMove(float deltaTime);

	void Update(float deltaTime);

	void UpdateViewPosBeforeDraw(float interpolation);

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};