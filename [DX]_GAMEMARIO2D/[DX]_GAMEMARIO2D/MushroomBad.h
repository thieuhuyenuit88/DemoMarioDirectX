#pragma once
#include "DynamicObject.h"

class MushroomBad: public DynamicObject{
private:
public:
	MushroomBad(void);
	~MushroomBad(void);
	MushroomBad(MushroomBad* obj);

	bool isBeforeDeathFlatted;
	bool isBeforteDeathJumpUp;

	void setBeforeDeathFlatted(){
		isBeforeDeathFlatted = true;
		isBeforteDeathJumpUp = false;
	}

	void setBeforeDeathJumpUp(){
		isBeforteDeathJumpUp = true;
		isBeforeDeathFlatted = false;
	}
	void Init();
	void ProcessCollision(MyObject* obj);
	void ProcessCollision(MyObject* obj, int _dir);
	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation);
	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};