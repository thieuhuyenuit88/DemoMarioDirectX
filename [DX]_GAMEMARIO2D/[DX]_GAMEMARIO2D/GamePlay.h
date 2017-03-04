#pragma once
#include "IPlay.h"

class GamePlay: public IPlay
{
public:
	GamePlay(LPDIRECT3DDEVICE9 pDeviceDX);
	~GamePlay();

	void Init();
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation);
	void Draw();
	void Release();
};