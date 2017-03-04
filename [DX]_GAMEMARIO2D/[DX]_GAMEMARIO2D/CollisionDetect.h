#pragma once
#include "MyObject.h"
#include "DXDeviceManager.h"
#include <WinDef.h>

class CollisionDetect{
private:
	static CollisionDetect* instance;
	CollisionDetect(void);
public:
	~CollisionDetect(void);

	static CollisionDetect* getCollisionDetect(){
		if (instance == NULL)
		{
			instance = new CollisionDetect();
		}
		return instance;
	}

	CRECT GetSweptBroadphaseBox(MyObject* obj){
		CRECT broadphasebox (0.0f, 0.0f, 0.0f, 0.0f);
		
		broadphasebox.left = obj->getVX()>0 ? obj->getPosX(): obj->getPosX() + obj->getVX()*DXDeviceManager::getInstanceDXDevice()->getDeltaTime();
		broadphasebox.top = obj->getVY()>0 ? obj->getPosY() + obj->getVY()*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() : obj->getPosY();
		broadphasebox.right = obj->getVX()>0 ? obj->getPosX() + obj->getVX()*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() + obj->getSizeWidth():
			obj->getPosX() + obj->getSizeWidth();
		broadphasebox.bottom = obj->getVY()>0 ? obj->getPosY() - obj->getSizeHeight(): obj->getPosY() + obj->getVY()*DXDeviceManager::getInstanceDXDevice()->getDeltaTime() - obj->getSizeHeight();
		
		return broadphasebox;
	}

	float SweptAABB(MyObject* obj1, MyObject* obj2, float& normalx, float& normaly){

		float xInvEntry, yInvEntry;
		float xInvExit, yInvExit;

		if (obj1->getVX() > 0.0f)
		{
			xInvEntry = obj2->getPosX() - (obj1->getPosX() + obj1->getSizeWidth());
			xInvExit = (obj2->getPosX() + obj2->getSizeWidth()) - obj1->getPosX();
		} 
		else 
		{
			xInvEntry = (obj2->getPosX() + obj2->getSizeWidth()) - obj1->getPosX();
			xInvExit = obj2->getPosX() - (obj1->getPosX() + obj1->getSizeWidth());	
		}

		if (obj1->getVY() > 0.0f)
		{
			yInvEntry = (obj2->getPosY() - obj2->getSizeHeight()) - obj1->getPosY();
			yInvExit = obj2->getPosY() - (obj1->getPosY() - obj1->getSizeHeight());
		} 
		else 
		{
			yInvEntry = obj2->getPosY() - (obj1->getPosY() - obj1->getSizeHeight());
			yInvExit = (obj2->getPosY() - obj2->getSizeHeight()) - obj1->getPosY();	
		}

		float xEntry, yEntry;
		float xExit, yExit;

		if (obj1->getVX() == 0.0f)
		{
			xEntry = -numeric_limits<float>::infinity();
			xExit = numeric_limits<float>::infinity();
		}
		else
		{
			xEntry = xInvEntry / (obj1->getVX()*DXDeviceManager::getInstanceDXDevice()->getDeltaTime());
			xExit = xInvExit / (obj1->getVX()*DXDeviceManager::getInstanceDXDevice()->getDeltaTime());
		}

		if (obj1->getVY() == 0.0f)
		{
			yEntry = -numeric_limits<float>::infinity();
			yExit = numeric_limits<float>::infinity();
		}
		else
		{
			yEntry = yInvEntry / (obj1->getVY()*DXDeviceManager::getInstanceDXDevice()->getDeltaTime());
			yExit = yInvExit / (obj1->getVY()*DXDeviceManager::getInstanceDXDevice()->getDeltaTime());
		}

		float entryTime = max(xEntry, yEntry);
		float exitTime = min(xExit, yExit);	

		if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
		{
			normalx = 0.0f;
			normaly = 0.0f;
			return 1.0f;
		} 
		else 
		{
			if (xEntry > yEntry)
			{
				if (xInvEntry < 0.0f)
				{
					normalx = 1.0f;
					normaly = 0.0f;
					if (yEntry == 0.0f)
					{
						if (obj1->getPosY() - obj1->getSizeHeight() >= obj2->getPosY() && obj1->getVY() < 0.0f)
						{
							normalx = 1.0f;
							normaly = 1.0f;
						}
						else if (obj1->getPosY() <= obj2->getPosY() - obj2->getSizeHeight() && obj1->getVY() > 0.0f)
						{
							normalx = 1.0f;
							normaly = -1.0f;
						}
						else{
							normalx = 1.0f;
							normaly = 0.0f;
						}
					}
				}
				else
				{				
					if (xInvEntry == 0.0f && obj1->getVX() < 0.0f)
					{
						normalx = 1.0f;
						normaly = 0.0f;
						if (yEntry == 0.0f)
						{
							if (obj1->getPosY() - obj1->getSizeHeight() >= obj2->getPosY()  && obj1->getVY() < 0.0f)
							{
								normalx = 1.0f;
								normaly = 1.0f;
							}
							else if (obj1->getPosY() <= obj2->getPosY() - obj2->getSizeHeight() && obj1->getVY() > 0.0f)
							{
								normalx = 1.0f;
								normaly = -1.0f;
							}
							else{
								normalx = 1.0f;
								normaly = 0.0f;
							}
						}
					}else{
						normalx = -1.0f;
						normaly = 0.0f;
						if (yEntry == 0.0f)
						{
							if (obj1->getPosY() - obj1->getSizeHeight() >= obj2->getPosY() && obj1->getVY() < 0.0f)
							{
								normalx = -1.0f;
								normaly = 1.0f;
							}
							else if (obj1->getPosY() <= obj2->getPosY() - obj2->getSizeHeight() && obj1->getVY() > 0.0f)
							{
								normalx = -1.0f;
								normaly = -1.0f;
							}
							else{
								normalx = -1.0f;
								normaly = 0.0f;
							}
						}
					}
				}
			}
			else
			{
				if (yInvEntry < 0.0f)
				{
					normalx = 0.0f;
					normaly = 1.0f;
				}
				else
				{				
					normalx = 0.0f;
					normaly = -1.0f;
					if (yInvEntry == 0 && obj1->getVY() < 0.0f && obj1->getPosY() - obj1->getSizeHeight() >= obj2->getPosY())
					{
						normalx = 0.0f;
						normaly = 1.0f;
					}
				}
			}
			return entryTime;
		}
	}

	float CollisionDir(MyObject* obj1, MyObject* obj2, float& normalx, float& normaly){
		CRECT BroadphaseBox1 = GetSweptBroadphaseBox(obj1);
		CRECT BroadphaseBox2 = GetSweptBroadphaseBox(obj2);

		if (BroadphaseBox1.isCollision(BroadphaseBox2))
		{
			return SweptAABB(obj1, obj2, normalx, normaly);
		}
		return 1.0f;
	}
};