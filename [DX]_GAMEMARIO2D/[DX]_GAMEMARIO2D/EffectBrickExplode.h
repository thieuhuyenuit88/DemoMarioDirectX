#pragma once
#include "Effect.h"
#include "Break.h"
#include <vector>

using namespace std;

class EffectBrickExplode: public Effect{
private:
	vector<Break*> *listSpriteExplode;

public:
	EffectBrickExplode(void);
	EffectBrickExplode(float x, float y);
	~EffectBrickExplode(void);

	void Init();

	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);

	void UpdateViewPosBeforeDraw(float interpolation);

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};