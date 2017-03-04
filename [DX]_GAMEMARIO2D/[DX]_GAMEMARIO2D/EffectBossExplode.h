#pragma once
#include "Effect.h"
#include "BossBreak.h"
#include <vector>

using namespace std;

class EffectBossExplode: public Effect{
private:
	vector<BossBreak*> *listSpriteExplode;

public:
	EffectBossExplode(void);
	EffectBossExplode(float x, float y);
	~EffectBossExplode(void);

	void Init();

	void UpdateAnimation(float deltaTime);
	void UpdateStatus(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);

	void UpdateViewPosBeforeDraw(float interpolation);

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};