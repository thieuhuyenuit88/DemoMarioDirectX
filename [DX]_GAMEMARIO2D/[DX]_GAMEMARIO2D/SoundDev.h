#pragma once
#include "dsutil.h"
#include "dxutil.h"

class DXSound{
private:
	HWND pHwnd;
	CSoundManager* pDXSound;
public:
	DXSound(void);
	~DXSound(void);

	bool Init(HWND _hwnd);
	CSound* LoadSound(char* fileName);
	void Release();
};
