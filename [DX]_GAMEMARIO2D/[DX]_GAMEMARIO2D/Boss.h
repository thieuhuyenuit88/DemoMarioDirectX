#pragma once
#include "DynamicObject.h"

class Boss: public DynamicObject{
private:
	float scaleX;
	float scaleY;
	float colorA;
	float timeChangeMove;
	float timeShot;
public:
	Boss(void);
	~Boss(void);
	Boss(Boss* obj);

	bool isNormaling;
	bool isShotting;
	bool isHurtting;
	int blood;

	void setNormaling(){
		isNormaling = true;
		isShotting = isHurtting = false;
	}

	void setShotting(){
		isShotting = true;
		isNormaling = isHurtting = false;
	}

	void setHurtting(){
		isHurtting = true;
		isNormaling = isShotting = false;
	}

	void updateShot(float deltaTime);

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