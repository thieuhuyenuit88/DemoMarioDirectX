#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class DXFont{
private:
	LPD3DXFONT pFont;
	D3DXFONT_DESC fontDesc;
	char* nameFont;
	int sizeFont;
	bool isItalic;

	void setDescFont(char* pathNameSource, char* name, int height, bool isItalic);
public:
	DXFont(void);
	DXFont(LPDIRECT3DDEVICE9 pDevice, char* pathNameSource, char* name, int height, bool isItalic);
	~DXFont(void);

	void RenderText(int posX, int posY, char* text, D3DXCOLOR color);
	void Realease();
};