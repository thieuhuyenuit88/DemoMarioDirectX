#pragma once
#include "DynamicObject.h"

class Turtle: public DynamicObject{
protected:
public:
	Turtle(void);
	~Turtle(void);
	Turtle(Turtle* obj);

	bool isNormaling;
	bool isStaticing;
	bool isRunning;

	void setNormaling(){
		isNormaling = true;
		isRunning = isStaticing = false;
	}

	void setStaticing(){
		isStaticing = true;
		isRunning = isNormaling = false;
	}

	void setRunning(){
		isRunning = true;
		isNormaling = isStaticing = false;
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