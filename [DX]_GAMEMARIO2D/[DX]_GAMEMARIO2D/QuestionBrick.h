#pragma once
#include "DynamicObject.h"

class QuestionBrick: public DynamicObject{
private:
	DynamicObject* hideObject;
public:
	QuestionBrick(void);
	~QuestionBrick(void);
	QuestionBrick(QuestionBrick* obj);

	DynamicObject* getHideObject(){
		return hideObject;
	}

	void setHideObject(DynamicObject* obj)
	{
		hideObject = obj;
	}

	bool isNormaling;
	bool isStaticing;

	void setNormaling(){
		isNormaling = true;
		isStaticing = false;
	}

	void setStaticing(){
		isStaticing = true;
		isNormaling = false;
	}

	void Init();
	void ProcessCollision(MyObject* obj);
	void ProcessCollision(MyObject* obj, int _dir);

	void UpdateAnimation(float deltaTime);

	void UpdateStatus(float deltaTime){}
	void UpdateMove(float deltaTime){}

	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation){}

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};