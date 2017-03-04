#pragma once
#include "DynamicObject.h"

class Mushroom:public DynamicObject{
private:
	float startPosY;
public:
	Mushroom(void);
	~Mushroom(void);
	Mushroom(Mushroom* obj);

	void setID(int id){
		oID = id;
		if (oID == MUSHROOMBIG)
		{
			iDynamicSprite.setCurFrame(0);
		}else
		if (oID == MUSHROOMUP)
		{
			iDynamicSprite.setCurFrame(1);
		}
	}

	float getStartPosY(){
		return startPosY;
	}

	void setY(float y){
		oPosY = startPosY = y;
	}

	void setXY(float x, float y){
		oPosX = x;
		oPosY = startPosY = y;
	}

	bool isNormaling;
	bool isUpping;

	void setNormaling(){
		isNormaling = true;
		isUpping = false;
	}

	void setUpping(){
		isUpping = true;
		isNormaling = false;
	}

	void Init();
	void ProcessCollision(MyObject* obj);
	void ProcessCollision(MyObject* obj,int _dir);

	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation){}
	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};