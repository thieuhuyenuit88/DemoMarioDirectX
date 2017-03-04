#pragma once
#include "CRECT.h"
#include <d3dx9.h>
#include "Global.h"
#include "ISprite.h"
#include "DXDeviceManager.h"
#include <stdio.h>
#include <limits>

using namespace std;

class MyObject{
protected:
	int oID;
	int oDirect;

	/*Status*/
	int oSTT, oOldSTT;
	
	/*Position*/
	float oPosX, oPosY;

	/*Position to render*/
	float oPosViewX, oPosViewY;
	float oVxView, oVyView;

	/*Velocity*/
	float oVx, oVy;

	/*Accel*/
	float oAccelX, oAccelY;

	/*Gravity*/
	float oGravity;

	/*Size*/
	float sizeWidth, sizeHeight;

	/*delta time*/
	float deltaTimeUpdate;

	/*Time update*/
	float timeUpdate;

	/*Time Animation*/
	float timeAnimate;

	/*Info sprite*/
	ISprite infoSprite;
public:
	MyObject(void);
	virtual ~MyObject(void);
	MyObject(MyObject *obj);

	CRECT getRect(){
		CRECT rect;
		rect.top = oPosY;
		rect.bottom = oPosY - sizeHeight;
		rect.left = oPosX;
		rect.right = oPosX + sizeWidth;
		return rect;
	}
	
	void setVX(float vx){
		oVx = vx;
	}

	void setVY(float vy){
		oVy = vy;
	}

	void setVXVY(float vx, float vy){
		oVx = vx;
		oVy = vy;
	}

	void setX(float x){
		oPosX = x;
	}

	void setY(float y){
		oPosY = y;
	}

	void setXY(float x, float y){
		oPosX = x;
		oPosY = y;
	}

	void setDirect(int dir){
		oDirect = dir;
	}

	void setID(int id){
		oID = id;
	}

	float getVX(){
		return oVx;
	}

	float getVY(){
		return oVy;
	}

	float getAccelX(){
		return oAccelX;
	}

	float getAccelY(){
		return oAccelY;
	}

	void setAccelY(float accelY){
		oAccelY = accelY;
	}

	void setAccelX(float accelX){
		oAccelX = accelX;
	}

	float getTimeUpdate(){
		return timeUpdate;
	}

	float getTimeAnimae(){
		return timeAnimate;
	}

	int getDirect(){
		return oDirect;
	}

	int getID(){
		return oID;
	}

	int getSTT(){return oSTT;}
	int getOldSTT(){return oOldSTT;}

	float getSizeWidth(){return sizeWidth;}
	float getSizeHeight(){return sizeHeight;}

	float getPosX(){return oPosX;}
	float getPosY(){return oPosY;}

	float getViewPosX(){return oPosViewX;}
	float getViewPosY(){return oPosViewY;}

	void setSTT(int stt){
		oSTT =stt;
	}

	void setOldSTT(int oldStt){
		oOldSTT = oldStt;
	}

	void setSize(float width, float height){
		sizeWidth = width;
		sizeHeight = height;
	}

	void setSizeWidth(float width){
		sizeWidth = width;
	}

	void setSizeHeight(float height){
		sizeHeight = height;
	}

	void setViewX(float x){
		oPosViewX = x;
	}

	void setViewY(float y){
		oPosViewY = y;
	}

	void setViewXY(float x, float y){
		oPosViewX = x;
		oPosViewY = y;
	}
	virtual bool isCollision(MyObject* obj);
	virtual int DirectionCollision(MyObject* obj);

	virtual void Init() = 0;
	virtual void ProcessCollision(MyObject* obj) = 0;
	
	virtual void UpdateAnimation(float deltaTime) = 0;
	virtual void UpdateStatus(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void Draw(LPD3DXSPRITE spriteHandler, D3DXMATRIX matrixWorld) = 0;
	virtual void Realease() = 0;
};