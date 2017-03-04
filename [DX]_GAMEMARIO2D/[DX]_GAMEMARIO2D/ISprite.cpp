#include "ISprite.h"

ISprite::ISprite(void)
{
	posX			= 0;
	posY			= 0;
	widthImage		= 0;
	heightImage		= 0;
	depth			= 0.0f;
	curFrame		= 0;
	scaleX			= 1.0f;
	scaleY			= 1.0f;
	rotation		= 0.0f;
	color			= D3DXCOLOR(1,1,1,1);
}


ISprite::~ISprite(void)
{
}

void ISprite::AnimateNextFrame(int first, int lenght){ //from first to first + lenght - 1
	if (curFrame < first)
	{
		curFrame = first;
	}else{
		if (curFrame > first + lenght - 1)
		{
			curFrame = first + lenght - 1;
		}else{
			curFrame++;
			if (curFrame > first + lenght - 1)
			{
				curFrame = first;
			}
		}
	}

}

void ISprite::AnimatePrevFrame(int first, int lenght){ //from first to first - lenght + 1
	if (curFrame > first)
	{
		curFrame = first;
	}else{
		if (curFrame < first - lenght + 1)
		{
			curFrame = first - lenght + 1;
		}else{
			curFrame--;
			if (curFrame < first - lenght + 1)
			{
				curFrame = first;
			}
		}
	}
}