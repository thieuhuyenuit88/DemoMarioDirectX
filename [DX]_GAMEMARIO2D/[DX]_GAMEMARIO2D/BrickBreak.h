#pragma once
#include "DynamicObject.h"

class BrickBreak: public DynamicObject{
protected:
	float startPosY;
public:
	BrickBreak(void);
	~BrickBreak(void);
	BrickBreak(BrickBreak* obj);

	bool isNormaling;
	bool isMoveUping;
	bool isMovingUpWithDeath;

	float getStartY(){
		return startPosY;
	}

	void setNormaling(){
		isNormaling = true;
		isMoveUping = isMovingUpWithDeath = false;
	}

	void setMoveUping(){
		isMoveUping = true;
		isNormaling = isMovingUpWithDeath = false;
	}

	void setMovingUpWithDeath(){
		isMovingUpWithDeath = true;
		isMoveUping = isNormaling = false;
	}

	void setY(float y){
		oPosY = startPosY = y;
	}

	void setXY(float x, float y){
		oPosX = x;
		startPosY = oPosY = y;
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

	void setMoveUp();
};