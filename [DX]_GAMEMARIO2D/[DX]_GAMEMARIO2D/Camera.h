#pragma once
#include "CRECT.h"
#include "MyObject.h"
#include <d3dx9.h>
#include "Global.h"

class Camera{
private:
	float width, height;
	float posX, posY;

	float offSetFreeZone;
public:
	Camera(void);
	Camera(float x, float y, float width, float height);
	~Camera(void);

	float getPosX(){return posX;}
	float getPosY(){return posY;}

	float getWidth(){return width;}
	float getHeight(){return height;}

	CRECT getRect(){
		CRECT rect;
		rect.top = posY + height;
		rect.bottom = posY;
		rect.left = posX;
		rect.right = posX + width;
		return rect;
	}

	CRECT getRectStatic(){
		CRECT rect;
		rect.top = posY + height;
		rect.bottom = posY;
		rect.left = posX - 100;
		rect.right = posX + width + 100;
		return rect;
	}

	CRECT getRectFreeZone(){
		CRECT rect;
		rect.left = posX + (g_SCREEN_WIDTH - offSetFreeZone)/2;
		rect.right = posX + (g_SCREEN_WIDTH - offSetFreeZone)/2 + offSetFreeZone;
		rect.top = posY + (g_SCREEN_HEIGHT - offSetFreeZone)/2 + offSetFreeZone;
		rect.bottom = posY + (g_SCREEN_HEIGHT - offSetFreeZone)/2;
		return rect;
	}

	void Update(MyObject* obj, float maxWidth, float maxHeight);
	D3DXMATRIX getMatrixTransform();
};