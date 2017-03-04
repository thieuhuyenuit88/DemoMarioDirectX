#pragma once
#include "StaticObject.h"

class Pipe: public StaticObject{
protected:
public:
	Pipe(void);
	~Pipe(void);

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