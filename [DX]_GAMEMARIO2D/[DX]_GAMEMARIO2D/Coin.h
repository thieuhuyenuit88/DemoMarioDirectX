#pragma once
#include "DynamicObject.h"

class Coin: public DynamicObject{
private:
	float rotaCoin;
public:
	Coin(void);
	~Coin(void);
	Coin(Coin* obj);

	void setStatusStart(int sttStart){
		oSTT = sttStart;
	}

	void Init();
	void ProcessCollision(MyObject* obj);
	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation){}
	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};