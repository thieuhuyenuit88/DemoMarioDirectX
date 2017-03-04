#include "DXFont.h"
#include "DXDeviceManager.h"
#include "Global.h"

DXFont::DXFont(void){
	pFont = NULL;
	nameFont = "";
	sizeFont = 0;
	isItalic = false;
}

DXFont::~DXFont(void){
	pFont->Release();
	pFont = NULL;
}

DXFont::DXFont(LPDIRECT3DDEVICE9 pDevice, char* pathNameSource, char* name, int height = 24, bool isItalic = false){
	nameFont = name;
	sizeFont = height;
	isItalic = isItalic;
	pFont = NULL;
	/******************************/
	setDescFont(pathNameSource, name, height, isItalic);
	
	HRESULT result = D3DXCreateFontIndirect(pDevice, &fontDesc, &pFont);
	if (FAILED(result))
	{
		MessageBox(DXDeviceManager::getInstanceDXDevice()->getHwnd(),"Could not create font","Warning!!",MB_OK);
	}

}

void DXFont::setDescFont(char* pathNameSource, char* name, int height, bool isItalic){
	
	AddFontResourceEx(pathNameSource, FR_PRIVATE, 0);

	ZeroMemory(&fontDesc, sizeof(fontDesc));
	fontDesc.Height = height;
	fontDesc.Width = 0;
	fontDesc.Weight = 500; //weight of font
	fontDesc.MipLevels = 0;
	fontDesc.Italic = isItalic;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_TT_PRECIS;
	fontDesc.Quality = CLIP_DEFAULT_PRECIS;
	fontDesc.PitchAndFamily = DEFAULT_PITCH;
	strcpy(fontDesc.FaceName, name);
}

void DXFont::RenderText(int posX, int posY, char* text, D3DXCOLOR color){
	RECT rect = {posX, posY, posX + g_SCREEN_WIDTH, posY + g_SCREEN_HEIGHT};
	pFont->DrawTextA(NULL, text, -1, &rect, DT_TOP | DT_LEFT, color);
}

void DXFont::Realease(){
	nameFont = NULL;
	pFont->Release();
	pFont = NULL;
}

