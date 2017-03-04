#pragma once
#include <d3dx9.h>
#include "Global.h"

class ISprite{
public:
	float posX, posY; // Position to render
	float widthImage, heightImage; // Size image
	float depth; // Depth 0 ~ 1

	int curFrame; // Current frame
	float scaleX, scaleY; // Scale image - Negative to mirror

	float rotation; // Rotation image - degree
	D3DXCOLOR color; // Color to blending - include Alpha

	ISprite(void);
	~ISprite(void);

	float getX () { return posX;}
	float getY () { return posY;}

	int getCurFrame () {return curFrame;}

	float getScaleX () {return scaleX;}
	float getScaleY () {return scaleY;}

	D3DXVECTOR2 getScale () {return D3DXVECTOR2(scaleX, scaleY);}

	float getRotation () {return rotation;}
	D3DXCOLOR getColor () {return color;}
	float getDepth () {return depth;}

	void setPosX(float x){
		posX = x;
	}

	void setPosY(float y){
		posY = y;
	}

	void setXY(float x, float y){
		posX = x;
		posY = y;
	}

	void setSize(float width, float height){
		this->widthImage = width;
		this->heightImage = height;
	}

	void setDepth(float depth){
		this->depth = depth;
	}

	void setScaleX(float scaleX){
		this->scaleX = scaleX;
	}

	void setScaleY(float scaleY){
		this->scaleY = scaleY;
	}

	void setScaleXY(float scaleX, float scaleY){
		this->scaleX = scaleX;
		this->scaleY = scaleY;
	}

	void setRotation(float rotation){
		this->rotation = rotation;
	}

	/* Set Color */
	/* value: 0 ~ 1 */
	void setColorRed(float red){
		color.r = red;
	}
	void setColorBlue(float blue){
		color.b = blue;
	}

	void setColorGreen(float green){
		color.g = green;
	}

	void setColorAlpha(float alpha){
		color.a = alpha;
	}

	void setColor(float red, float blue, float green, float alpha){
		color.r = red;
		color.b = blue;
		color.g = green;
		color.a = alpha;
	}

	void setCurFrame(int curFrame){
		this->curFrame = curFrame;
	}

	D3DXMATRIX getMatrixTransform2D()
	{
		D3DXMATRIX matrix; // To scale or rotate our sprites we need to use a matrix

		D3DXVECTOR2 mCenter((float)((widthImage)/2),(float)((heightImage)/2));
		D3DXVECTOR2 mScale(scaleX,scaleY); //
		D3DXVECTOR2 mTrans (posX, posY);// g_SCREEN_HEIGHT - posY); //transform origin (0,0) to bottom left
		float mRotation = (float)(rotation * 2 * D3DX_PI)/(float)(360); // change from degree to radian or use D3DXToRadian(rotation)

		// out, scaling center, scaling rotation, scaling, rotation center, rotation, translation
		D3DXMatrixTransformation2D(&matrix,&mCenter,0,&mScale,&mCenter,mRotation,&mTrans);
		return matrix;
	}

	void AnimateNextFrame(int first, int lenght);
	void AnimatePrevFrame(int first, int lenght);
};