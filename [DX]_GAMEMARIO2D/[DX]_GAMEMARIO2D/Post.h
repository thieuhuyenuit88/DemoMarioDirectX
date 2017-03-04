#pragma once
#include "StaticObject.h"

class Post: public StaticObject{
protected:
public:
	Post(void);
	~Post(void);

	void setIDCurFrame(int curFrameID){
		iStaticSprite.setCurFrame(curFrameID);
	}

	void Init();
	void ProcessCollision(MyObject* obj){}

	void UpdateAnimation(float deltaTime){}
	void UpdateStatus(float deltaTime){}
	void Update(float deltaTime){}

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};