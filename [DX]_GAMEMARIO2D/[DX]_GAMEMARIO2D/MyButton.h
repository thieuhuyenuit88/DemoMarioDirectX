#pragma once
#include "CCallBack.h"
#include "Sprite.h"
#include "ISprite.h"

template <class cInstance>
class MyButton{
public:
	CCallBack<cInstance> * fire;

	int idBtn;

	Sprite* skinButton;
	ISprite iSkinButton;

	bool isEnable;
	bool isVisible;

	float posBtnX;
	float posBtnY;
	ButtonStatus sttButton;
	
	MyButton(void){
		isEnable = true;
		isVisible = true;
		sttButton = NORMAL;
		fire = new CCallBack<cInstance>();
	}

	MyButton(Sprite* _skinBtn, float _posX, float _posY, int _idBtn){
		skinButton = _skinBtn;
		posBtnX = _posX;
		posBtnY = _posY;
		isEnable = true;
		isVisible = true;
		sttButton = NORMAL;

		fire = new CCallBack<cInstance>();
		idBtn = _idBtn;
	}
	
	~MyButton(void){

	}

	void setPosBtn(float _posX, float _posY){
		posBtnX = _posX;
		posBtnY = posBtnY;
	}

	void UpdateInput(int btnChoosing, bool isFire){
		if (isEnable && isVisible)
		{
			if (btnChoosing == idBtn)
			{
				sttButton = CHOOSED;
				if (isFire)
				{
					fire->Execute(idBtn);
					sttButton = FIRED;
				}
			}else{
				sttButton = NORMAL;
			}
		}
	}

	void Draw(LPD3DXSPRITE spriteHandler){
		if (isVisible)
		{
			if (sttButton == CHOOSED || sttButton == FIRED)
			{
				iSkinButton.curFrame = 1;
				if (sttButton == FIRED)
				{
					iSkinButton.setScaleXY(1.1f, 1.1f);
					iSkinButton.setXY(posBtnX, posBtnY);
					skinButton->Draw(spriteHandler, iSkinButton);
					iSkinButton.setScaleXY(1.0f, 1.0f);
				}else if (sttButton == CHOOSED)
				{
					iSkinButton.setScaleXY(1.0f, 1.0f);
					iSkinButton.setXY(posBtnX, posBtnY);
					skinButton->Draw(spriteHandler, iSkinButton);
				}
			}else if (sttButton == NORMAL)
			{
				iSkinButton.curFrame = 0;
				iSkinButton.setScaleXY(1.0f, 1.0f);
				iSkinButton.setXY(posBtnX, posBtnY);
				skinButton->Draw(spriteHandler, iSkinButton);
			}
		}
	}
};