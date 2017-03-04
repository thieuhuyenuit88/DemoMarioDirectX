#include "Sprite.h"
#include "DXDeviceManager.h"

Sprite::~Sprite(void){
	if (pTexture != NULL)
	{
		pTexture->Release();
		pTexture = NULL;
	}
}

Sprite::Sprite(LPDIRECT3DDEVICE9 pDevice, char* pathNameSource, int with, int height, int column, D3DCOLOR colorTrans /* = D3DCOLOR_XRGB */){
	withFrame = with;
	heightFrame = height;
	columnFrame = column;

	// Get texture from file
	D3DXIMAGE_INFO infoImage;
	HRESULT result;
	result = D3DXGetImageInfoFromFile(pathNameSource, &infoImage);
	if (result != D3D_OK)
	{
		return;
	}

	result = D3DXCreateTextureFromFileEx(pDevice,
		pathNameSource,
		infoImage.Width,
		infoImage.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorTrans,
		&infoImage,
		NULL,
		&pTexture);
	if (result != D3D_OK)
	{
		MessageBox(DXDeviceManager::getInstanceDXDevice()->getHwnd(), "Load texture fail","Error",MB_OK);
		return;
	}
}

void Sprite::Realease(){
	if (pTexture!=NULL)
	{
		pTexture->Release();
		pTexture = NULL;
	}
}

void Sprite::Draw(LPD3DXSPRITE spriteHandler, D3DMATRIX matrixWorld, float posX, float posY, int indexFrame, float depth /* = 0 */, D3DXCOLOR color /* = D3DXCOLOR */){
	D3DXMATRIX matrix, matrixResult;

	D3DXMatrixIdentity(&matrixResult);
	D3DXVECTOR2 mTrans (posX,posY); 

	D3DXMatrixTransformation2D(&matrix,NULL,0,NULL,NULL,NULL,&mTrans);
	matrixResult = matrix * matrixWorld;
	spriteHandler->SetTransform(&matrixResult);

	// Draw(LPDIRECT3DTEXTURE9 pSrcTexture, CONST RECT *pSrcRect, D3DXVECTOR3 *center, CONST D3DVECTOR3 *pTranslation,  D3DCOLOR Color );
	spriteHandler->Draw(pTexture, &this->getRectFrameInImage(indexFrame), NULL,
		&D3DXVECTOR3(0,0,depth),color);
}

void Sprite::Draw(LPD3DXSPRITE spriteHandler, float posX, float posY, int indexFrame){
	D3DXMATRIX matrixResult;

	D3DXMatrixIdentity(&matrixResult);
	D3DXVECTOR2 mTrans (posX,posY); 

	D3DXMatrixTransformation2D(&matrixResult,NULL,0,NULL,NULL,NULL,&mTrans);
	spriteHandler->SetTransform(&matrixResult);

	// Draw(LPDIRECT3DTEXTURE9 pSrcTexture, CONST RECT *pSrcRect, D3DXVECTOR3 *center, CONST D3DVECTOR3 *pTranslation,  D3DCOLOR Color );
	spriteHandler->Draw(pTexture, &this->getRectFrameInImage(indexFrame), NULL,
		&D3DXVECTOR3(0,0,0), D3DCOLOR_ARGB(255,255,255,255));
}

void Sprite::Draw(LPD3DXSPRITE spriteHandler, D3DMATRIX matrixWorld, ISprite iSprite){
	D3DXMATRIX matrixResult;
	D3DXMATRIX matrixChangeCoords;
	D3DXVECTOR2 mTranCoords (0, g_SCREEN_HEIGHT - 2*iSprite.getY()); //transform origin (0,0) to bottom left

	D3DXMatrixIdentity(&matrixResult);
	D3DXMatrixIdentity(&matrixChangeCoords);
	D3DXMatrixTransformation2D(&matrixChangeCoords,NULL,0,NULL,NULL,NULL,&mTranCoords);

	matrixResult = iSprite.getMatrixTransform2D() * matrixWorld * matrixChangeCoords;
	spriteHandler->SetTransform(&matrixResult);

	// Draw(LPDIRECT3DTEXTURE9 pSrcTexture, CONST RECT *pSrcRect, D3DXVECTOR3 *center, CONST D3DVECTOR3 *pTranslation,  D3DCOLOR Color );
	spriteHandler->Draw(pTexture, &this->getRectFrameInImage(iSprite.getCurFrame()), NULL,
		&D3DXVECTOR3(0,0,iSprite.getDepth()), iSprite.getColor());
}

void Sprite::Draw(LPD3DXSPRITE spriteHandler, ISprite iSprite)
{
	spriteHandler->SetTransform(&iSprite.getMatrixTransform2D());

	// Draw(LPDIRECT3DTEXTURE9 pSrcTexture, CONST RECT *pSrcRect, D3DXVECTOR3 *center, CONST D3DVECTOR3 *pTranslation,  D3DCOLOR Color );
	spriteHandler->Draw(pTexture, &this->getRectFrameInImage(iSprite.getCurFrame()), NULL,
		&D3DXVECTOR3(0,0,iSprite.getDepth()), iSprite.getColor());
}

void Sprite::DrawCenter(LPD3DXSPRITE spriteHandler, ISprite iSprite)
{
	spriteHandler->SetTransform(&iSprite.getMatrixTransform2D());

	// Draw(LPDIRECT3DTEXTURE9 pSrcTexture, CONST RECT *pSrcRect, D3DXVECTOR3 *center, CONST D3DVECTOR3 *pTranslation,  D3DCOLOR Color );
	spriteHandler->Draw(pTexture, &this->getRectFrameInImage(iSprite.getCurFrame()), NULL,
		&D3DXVECTOR3(float(withFrame/2), float(heightFrame/2),iSprite.getDepth()), iSprite.getColor());
}