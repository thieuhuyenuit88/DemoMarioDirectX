#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "ISprite.h"

class Sprite{
private:
	LPDIRECT3DTEXTURE9 pTexture; // point to texture
	int curFrame, columnFrame;

	int withFrame, heightFrame;
public:
	Sprite(LPDIRECT3DDEVICE9 pDevice, char* pathNameSource, int with, int height, int column, D3DCOLOR colorTrans = D3DCOLOR_XRGB(255,0,255));
	virtual ~Sprite(void);

	void setSize(int with, int heigth){
		withFrame = with;
		heightFrame = heigth;
	}

	void setTexture(LPDIRECT3DTEXTURE9 texture){
		this->pTexture = texture;
	}

	void setColumn(int column){ columnFrame = column;}
	void setCurFrame(int curFrame){this->curFrame = curFrame;}

	D3DXVECTOR2 getSizeFrame(){
		D3DXVECTOR2 sizeFrame = D3DXVECTOR2(float(withFrame), float(heightFrame));
		return sizeFrame;
	}

	LPDIRECT3DTEXTURE9 getTexture(){
		return pTexture;
	}

	int getColumn(){return columnFrame;}
	int getCurFrame(){ return curFrame;}

	RECT getRectFrameInImage(int frame){
		RECT rect;
		rect.top = (frame/columnFrame) * heightFrame;
		rect.bottom = rect.top + heightFrame;
		rect.left = (frame%columnFrame) * withFrame;
		rect.right = rect.left + withFrame;
		return rect;
	}

	void Draw(LPD3DXSPRITE spriteHandler, D3DMATRIX matrixWorld, 
		float posX, float posY, int indexFrame, float depth = 0, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));
	void Draw(LPD3DXSPRITE spriteHandler, float posX, float posY, int indexFrame);
	void Draw(LPD3DXSPRITE spriteHandler, D3DMATRIX matrixWorld, ISprite iSprite);
	void Draw(LPD3DXSPRITE spriteHandler, ISprite iSprite);
	void DrawCenter(LPD3DXSPRITE spriteHandler, ISprite iSprite);
	void Realease();
};