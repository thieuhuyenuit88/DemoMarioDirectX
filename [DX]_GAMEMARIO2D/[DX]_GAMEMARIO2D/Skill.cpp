#include "Skill.h"

Skill::Skill(void): DynamicObject(){

}

Skill::Skill(float x, float y):DynamicObject()
{
	setXY(x, y);
}

Skill::Skill(Skill* obj):DynamicObject(obj){

}

Skill::~Skill(void){

}

void Skill::Realease(){
	DynamicObject::Realease();
}
