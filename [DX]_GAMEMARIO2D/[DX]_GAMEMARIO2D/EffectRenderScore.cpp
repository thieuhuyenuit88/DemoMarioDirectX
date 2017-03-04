#include "EffectRenderScore.h"
#include "Global.h"
#include <stdio.h>

EffectRenderScore::EffectRenderScore(void):Effect(){
	Init();
}

EffectRenderScore::EffectRenderScore(DXFont* _fontRender, float x, float y, int _score):Effect(x,y){
	fontRender = _fontRender;
	score = _score;
	strScore = new char[100];
	sprintf(strScore, "%d", score);
	Init();
}

EffectRenderScore::~EffectRenderScore(void){

}

void EffectRenderScore::Init(){
	oSTT = ACTIVE;
}

void EffectRenderScore::UpdateMove(float deltaTime){
	if (oSTT == ACTIVE)
	{
		oPosY += 2;
		timeUpdate += deltaTime;
		if (timeUpdate > 800)
		{
			timeUpdate = 0;
			oSTT = DEATH;
		}
	}

}


void EffectRenderScore::Update(float deltaTime){
	UpdateMove(deltaTime);
}

void EffectRenderScore::Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld){
	if (oSTT == ACTIVE)
	{
		fontRender->RenderText(oPosX + matrixWorld._41, 
			g_SCREEN_HEIGHT - oPosY + matrixWorld._42, strScore, D3DXCOLOR(255,215,0,255));
	}
}

void EffectRenderScore::Realease(){
	delete strScore;
	strScore = NULL;
}