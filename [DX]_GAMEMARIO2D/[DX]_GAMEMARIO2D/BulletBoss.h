#pragma once
#include "Skill.h"

class BulletBoss: public Skill{
private:
public:
	BulletBoss(void);
	BulletBoss(float x, float y);
	~BulletBoss(void);
	BulletBoss(BulletBoss* obj);

	void setDirect(int direct){
		oDirect = direct;
		oVx = oDirect * 0.6f;
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

