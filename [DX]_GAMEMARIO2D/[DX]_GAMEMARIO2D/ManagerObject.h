#pragma once
#include "Effect.h"
#include "Skill.h"
#include "MyObject.h"
#include <vector>

using namespace std;

class ManagerObject{
private:
	static ManagerObject* instance;
	
	vector<Effect*> *listEffect;
	vector<Skill*> *listSkill;
	vector<MyObject*> *listDynamicObject;
	ManagerObject(void);
public:
	~ManagerObject(void);

	static ManagerObject* getManagerObject(){
		if (instance == NULL)
		{
			instance = new ManagerObject();
		}
		return instance;
	}

	vector<Effect*>* getListEffect(){
		return listEffect;
	}

	void setListEffect(vector<Effect*> *_listEffect){
		listEffect = _listEffect;
	}

	vector<Skill*>* getListSkill(){
		return listSkill;
	}

	void setListSkill(vector<Skill*> *_listSkill){
		listSkill = _listSkill;
	}

	vector<MyObject*>* getListDynamicObject(){
		return listDynamicObject;
	}

	void setListDynamicObject(vector<MyObject*> *_listObject){
		listDynamicObject = _listObject;
	}
};