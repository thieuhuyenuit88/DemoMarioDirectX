#include "Camera.h"

Camera::Camera(void){
	posX = posY = width = height = 0;
	offSetFreeZone = g_OFFSETFREEZONE;
}

Camera::Camera(float x, float y, float width, float height)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	offSetFreeZone = g_OFFSETFREEZONE;
}

Camera::~Camera(void){

}

void Camera::Update(MyObject* obj, float maxWidth, float maxHeight){
	CRECT rect;
	rect = getRectFreeZone();

	if (obj->getSTT() == ACTIVE)
	{
		float posCharacterX = obj->getPosX() + obj->getSizeWidth()/2;
		float posCharacterY = obj->getPosY() - obj->getSizeHeight()/2;

		if (posCharacterX > rect.right)
		{
			posX += posCharacterX - rect.right;
		}else if (posCharacterX < rect.left)
		{
			posX += posCharacterX - rect.left;
		}

		if (posX <= 0)
		{
			posX = 0;
		}else if (posX >= maxWidth - g_SCREEN_WIDTH)
		{
			posX = maxWidth - g_SCREEN_WIDTH - 1;
		}

		if (posCharacterY > rect.top)
		{
			posY += posCharacterY - rect.top;
		}else if (posCharacterY < rect.bottom)
		{
			posY += posCharacterY - rect.bottom;
		}

		////Max height from bottom, left (0,0)
		if(posY >= 80){
			posY = 80;
		}


		if (posY < 0)
		{
			posY = 0;
		}
	}
}

D3DXMATRIX Camera::getMatrixTransform(){
	// Transform matrix camera
	D3DXMATRIX matrixTransCamera;
	D3DXMatrixIdentity(&matrixTransCamera);

	D3DXVECTOR2 mTrans(-posX, posY);// transform world with camera transform
	D3DXMatrixTransformation2D(&matrixTransCamera,NULL,0,NULL,NULL,NULL,&mTrans);

	/*....*/
	// Maybe add some effect for camera from here, example: shake, scale...

	return matrixTransCamera;
}