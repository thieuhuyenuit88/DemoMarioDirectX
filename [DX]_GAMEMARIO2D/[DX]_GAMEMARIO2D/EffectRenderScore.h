#pragma once
#include "Effect.h"
#include "DXFont.h"

class EffectRenderScore: public Effect{
private:
	int score;
	DXFont* fontRender;
	char* strScore;
public:
	EffectRenderScore(void);
	EffectRenderScore(DXFont* _fontRender, float x, float y, int _score);
	~EffectRenderScore(void);

	void Init();

	void UpdateAnimation(float deltaTime){}
	void UpdateStatus(float deltaTime){}
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);

	void UpdateViewPosBeforeDraw(float interpolation){}

	void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld);
	void Realease();
};