#include "QuadTreeNode.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Boss.h"
#include "Turtle.h"
#include "QuestionBrick.h"
#include "BaseLand.h"
#include "Fence.h"
#include "Pipe.h"
#include "Pole.h"
#include "Post.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"

QuadTreeNode::QuadTreeNode(void){
	contents = new vector<MyObject*>();
	contentsDynamic = new vector<DynamicObject*>();
	contentsStatic = new vector<StaticObject*>();
	nodeChild = new vector<QuadTreeNode*>();
}

QuadTreeNode::QuadTreeNode(CRECT _bounds, string _strID){
	contents = new vector<MyObject*>();
	contentsDynamic = new vector<DynamicObject*>();
	contentsStatic = new vector<StaticObject*>();

	bounds = _bounds;
	nodeChild = new vector<QuadTreeNode*>();
	strNodeID = _strID;
}

QuadTreeNode::~QuadTreeNode(void){
	if (nodeChild != NULL)
	{
		nodeChild->clear();
		delete nodeChild;
	}

	if (contents != NULL)
	{
		contents->clear();
		delete contents;
	}
}

void QuadTreeNode::CreateSubNodes(){
	//the maximum level node <= 5 => length <= 9
	if (this->strNodeID.length() == 9)
	{
		return;
	}

	float halfWidth = (bounds.right - bounds.left)/2;
	float halfHeight = (bounds.top - bounds.bottom)/2;

	nodeChild->push_back(new QuadTreeNode(CRECT(bounds.left, bounds.left + halfWidth,
		bounds.top, bounds.top - halfHeight), this->strNodeID + string("00")));
	//nodeChild->at(0)->strNodeID = this->strNodeID + string("00");

	nodeChild->push_back(new QuadTreeNode(CRECT(bounds.left, bounds.left + halfWidth,
		bounds.top - halfHeight, bounds.bottom), this->strNodeID + string("01")));
	/*nodeChild->at(1)->strNodeID += this->strNodeID;
	nodeChild->at(1)->strNodeID += "01";*/

	nodeChild->push_back(new QuadTreeNode(CRECT(bounds.left + halfWidth, bounds.right,
		bounds.top - halfHeight, bounds.bottom), this->strNodeID + string("10")));
	/*nodeChild->at(2)->strNodeID += this->strNodeID ;
	nodeChild->at(2)->strNodeID += "10";*/

	nodeChild->push_back(new QuadTreeNode(CRECT(bounds.left + halfWidth, bounds.right,
		bounds.top, bounds.top - halfHeight), this->strNodeID + string("11")));
	/*nodeChild->at(3)->strNodeID += this->strNodeID;
	nodeChild->at(3)->strNodeID += "11";*/
}

void QuadTreeNode::CreateQuadTree(){
	if (nodeChild->size() == 0)
	{
		CreateSubNodes();
	}
	if (nodeChild->size() > 0)
	{
		for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
		{
			(*i)->CreateQuadTree();
		}
	}
}

vector<MyObject*>* QuadTreeNode::getSubTreeContents(){
	vector<MyObject*>* result = new vector<MyObject*>();
	
	vector<MyObject*>* temps = this->getContentsEx(); 
	result->insert(result->begin(),temps->begin(),temps->end());
	delete temps;

	if (nodeChild->size() > 0)
	{
		for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
		{
			vector<MyObject*>* subTemps = (*i)->getSubTreeContents();
			result->insert(result->begin(),subTemps->begin(),subTemps->end());
			delete subTemps;
		}
	}
	return result;
}

vector<DynamicObject*>* QuadTreeNode::getSubTreeContentsDynamic(){
	vector<DynamicObject*>* result = new vector<DynamicObject*>();

	vector<DynamicObject*>* temps = this->getContentsDynamicEx(); 
	result->insert(result->begin(),temps->begin(),temps->end());
	delete temps;

	if (nodeChild->size() > 0)
	{
		for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
		{
			vector<DynamicObject*>* subTemps = (*i)->getSubTreeContentsDynamic();
			result->insert(result->begin(),subTemps->begin(),subTemps->end());
			delete subTemps;
		}
	}
	return result;
}

vector<StaticObject*>* QuadTreeNode::getSubTreeContentsStatic(){
	vector<StaticObject*>* result = new vector<StaticObject*>();

	vector<StaticObject*>* temps = this->getContentsStaticEx(); 
	result->insert(result->begin(),temps->begin(),temps->end());
	delete temps;

	if (nodeChild->size() > 0)
	{
		for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
		{
			vector<StaticObject*>* subTemps = (*i)->getSubTreeContentsStatic();
			result->insert(result->begin(),subTemps->begin(),subTemps->end());
			delete subTemps;
		}
	}
	return result;
}

QuadTreeNode* QuadTreeNode::getNodeChildWithID(string _strID){
	QuadTreeNode* resultQtNode = NULL;

	if (this->strNodeID.compare(_strID) == 0)
	{
		resultQtNode = this;
		return resultQtNode;
	}
	if (nodeChild->size() > 0)
	{
		for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
		{
			resultQtNode = (*i)->getNodeChildWithID(_strID);
			if (resultQtNode != NULL)
			{
				return resultQtNode; 
			}
		}
	}

	return resultQtNode;
}

int QuadTreeNode::countObject(){
	int result = 0;
	result += contentsDynamic->size();
	result += contentsStatic->size();

	if (nodeChild->size() > 0)
	{
		for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
		{
			result += (*i)->countObject();
		}
	}
	return result;
}

bool QuadTreeNode::isEmpty(){
	if (this->countObject() > 0)
	{
		return false;
	}
	return true;
}

void QuadTreeNode::Insert(MyObject* obj){

	if (!bounds.isContain(obj->getRect()))
	{
		return;
	}

	if (nodeChild->size() == 0)
	{
		LEVELNODE++;
		CreateSubNodes();
	}

	/*if (nodeChild != NULL)
	{
		for (int i=0; i<4; i++)
		{
			if (nodeChild->at(i)->bounds.isContain(obj->getRect()))
			{
				nodeChild->at(i)->Insert(obj);
				return;
			}
		}
	}
	this->contents->push_back(obj);*/

	QuadTreeNode* destTree = getDestTreeNode(obj);
	if (destTree == this)
	{
		this->contents->push_back(obj);
	}else{
		destTree->Insert(obj);
	}
}

void QuadTreeNode::Insert(DynamicObject* obj){

	if (!bounds.isContain(obj->getRect()))
	{
		return;
	}

	if (nodeChild->size() == 0)
	{
		LEVELNODE++;
		CreateSubNodes();
	}

	QuadTreeNode* destTree = getDestTreeNode(obj);
	if (destTree == this)
	{
		this->contentsDynamic->push_back(obj);
	}else{
		destTree->Insert(obj);
	}
}

void QuadTreeNode::Insert(StaticObject* obj){

	if (!bounds.isContain(obj->getRect()))
	{
		return;
	}

	if (nodeChild->size() == 0)
	{
		LEVELNODE++;
		CreateSubNodes();
	}

	QuadTreeNode* destTree = getDestTreeNode(obj);
	if (destTree == this)
	{
		this->contentsStatic->push_back(obj);
	}else{
		destTree->Insert(obj);
	}
}

QuadTreeNode* QuadTreeNode::getDestTreeNode(MyObject* obj){
	QuadTreeNode* destTree =  this;
	for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
	{
		if ((*i)->bounds.isContain(obj->getRect()))
		{
			destTree = (*i);
		}
	}
	return destTree;
}

vector<MyObject*>* QuadTreeNode::Query(CRECT area){
	vector<MyObject*>* result = new vector<MyObject*>();
	
	if (area.isContain(bounds))
	{
		vector<MyObject*>* query = getSubTreeContents();
		result->insert(result->begin(), query->begin(), query->end());
		delete query;
		return result;
	}else if (area.isCollision(bounds))
	{
		for (vector<MyObject*>::iterator i = contents->begin(); i!= contents->end();)
		{
			if (area.isCollision((*i)->getRect()))
			{
				result->push_back((*i));
				i = contents->erase(i);
			}else{
				i++;
			}
		}

		if (nodeChild->size() > 0)
		{
			for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
			{
				if ((*i)->isEmpty())
				{
					continue;
				}else{
					vector<MyObject*>* query = (*i)->Query(area);
					result->insert(result->begin(), query->begin(), query->end());
					delete query;
				}
			}
		}
	}
	

	/*if (nodeChild->size() > 0)
	{
		for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
		{
			if ((*i)->isEmpty())
			{
				continue;
			}
			if ((*i)->bounds.isContain(area))
			{
				vector<MyObject*>* query = (*i)->Query(area);
				result->insert(result->begin(), query->begin(), query->end());
				delete query;
				break;
			}
			if (area.isContain((*i)->bounds))
			{
				vector<MyObject*>* query = (*i)->getSubTreeContents();
				result->insert(result->begin(), query->begin(), query->end());
				delete query;
			}
			if ((*i)->bounds.isCollision(area))
			{
				vector<MyObject*>* query = (*i)->Query(area);
				result->insert(result->begin(), query->begin(), query->end());
				delete query;
			}
		}
	}*/
	return result;
}

vector<DynamicObject*>* QuadTreeNode::QueryDN(CRECT area){
	vector<DynamicObject*>* result = new vector<DynamicObject*>();
	
	if (area.isContain(bounds))
	{
		vector<DynamicObject*>* query = getSubTreeContentsDynamic();
		result->insert(result->begin(), query->begin(), query->end());
		delete query;
		return result;
	}else if (area.isCollision(bounds))
	{
		for (vector<DynamicObject*>::iterator i = contentsDynamic->begin(); i!= contentsDynamic->end();)
		{
			if (area.isCollision((*i)->getRect()))
			{
				result->push_back((*i));
				i = contentsDynamic->erase(i);
			}else{
				i++;
			}
		}

		if (nodeChild->size() > 0)
		{
			for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
			{
				if ((*i)->isEmptyDN())
				{
					continue;
				}else{
					vector<DynamicObject*>* query = (*i)->QueryDN(area);
					result->insert(result->begin(), query->begin(), query->end());
					delete query;
				}
			}
		}
	}
	return result;
}

vector<StaticObject*>* QuadTreeNode::QueryST(CRECT area){
	vector<StaticObject*>* result = new vector<StaticObject*>();
	
	if (area.isContain(bounds))
	{
		vector<StaticObject*>* query = getSubTreeContentsStatic();
		result->insert(result->begin(), query->begin(), query->end());
		delete query;
		return result;
	}else if (area.isCollision(bounds))
	{
		for (vector<StaticObject*>::iterator i = contentsStatic->begin(); i!= contentsStatic->end();)
		{
			if (area.isCollision((*i)->getRect()))
			{
				result->push_back((*i));
				i = contentsStatic->erase(i);
			}else{
				i++;
			}
		}

		if (nodeChild->size() > 0)
		{
			for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
			{
				if ((*i)->isEmptyST())
				{
					continue;
				}else{
					vector<StaticObject*>* query = (*i)->QueryST(area);
					result->insert(result->begin(), query->begin(), query->end());
					delete query;
				}
			}
		}
	}
	return result;
}

void QuadTreeNode::SaveQuadTree(ofstream &tw){
	if (isEmpty())
	{
		return;
	}

	if (nodeChild->size() > 0)
	{
		for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
		{
			(*i)->SaveQuadTree(tw);
		}
	}

	if (contentsDynamic->size() > 0 || contentsStatic->size() > 0)
	{
		tw<<strNodeID.c_str()<<" ";

		if (contentsStatic->size() > 0)
		{
			for (vector<StaticObject*>::iterator i = contentsStatic->begin(); i!= contentsStatic->end(); i++)
			{
				tw<<(*i)->getID()<<" ";
				tw<<(int)(*i)->getPosX()<<" "<<(int)(*i)->getPosY()<<" ";
				if ((*i)->getID() == LAND_BASE)
				{
					tw<<((BaseLand*)(*i))->getISprite().getCurFrame()<<" ";
				}else if ((*i)->getID() == FENCE)
				{
					tw<<((Fence*)(*i))->getISprite().getCurFrame()<<" ";
				}else if ((*i)->getID() == PIPE)
				{
					tw<<((Pipe*)(*i))->getISprite().getCurFrame()<<" ";
				}else if ((*i)->getID() == POLE)
				{
					tw<<((Pole*)(*i))->getISprite().getCurFrame()<<" ";
				}else if ((*i)->getID() == POST)
				{
					tw<<((Post*)(*i))->getISprite().getCurFrame()<<" ";
				}else{
					tw<<(*i)->getSTT()<<" ";
				}
			}
		}

		if (contentsDynamic->size() > 0)
		{
			for (vector<DynamicObject*>::iterator i = contentsDynamic->begin(); i!= contentsDynamic->end(); i++)
			{
				tw<<(*i)->getID()<<" ";
				tw<<(int)(*i)->getPosX()<<" "<<(int)(*i)->getPosY()<<" ";
				if ((*i)->getID() == BOSS)
				{
					if ((*i)->getSTT() == ACTIVE)
					{
						tw<<((Boss*)(*i))->blood<<" ";
					}else{
						tw<<DEATH<<" ";
					}
					
				}else if ((*i)->getID() == TURTLE)
				{
					if (((Turtle*)(*i))->isNormaling)
					{
						tw<<11<<" ";
					}else if (((Turtle*)(*i))->isRunning || ((Turtle*)(*i))->isStaticing)
					{
						tw<<12<<" ";
					}else{
						tw<<DEATH<<" ";
					}
					
				}else if ((*i)->getID() == QUESTION_BRICK)
				{
					if (((QuestionBrick*)(*i))->isNormaling)
					{
						tw<<((QuestionBrick*)(*i))->getHideObject()->getID()<<" ";
					}else if (((QuestionBrick*)(*i))->isStaticing)
					{
						tw<<50<<" ";
					}

				}else if ((*i)->getID() == COIN)
				{
					if (((Coin*)(*i))->getSTT() == ACTIVE)
					{
						tw<<((Coin*)(*i))->getSTT()<<" ";
					}else if (((Coin*)(*i))->getSTT() == READY)
					{
						tw<<13<<" ";
					}if ((*i)->getSTT() == BEFORE_DEATH || (*i)->getSTT() == DEATH)
					{
						tw<<DEATH<<" ";
					}

				}else if ((*i)->getID() == FLOWER)
				{
					if (((Flower*)(*i))->getSTT() == ACTIVE)
					{
						if (((Flower*)(*i))->isUpping)
						{
							tw<<11<<" ";
						}
						if (((Flower*)(*i))->isNormaling)
						{
							tw<<12<<" ";
						}
					}else if (((Flower*)(*i))->getSTT() == READY)
					{
						tw<<13<<" ";
					}else{
						tw<<DEATH<<" ";
					}

				}
				else if ((*i)->getID() == MUSHROOMUP)
				{
					if (((Mushroom*)(*i))->getSTT() == ACTIVE)
					{
						if (((Mushroom*)(*i))->isUpping)
						{
							tw<<11<<" ";
						}
						if (((Mushroom*)(*i))->isNormaling)
						{
							tw<<12<<" ";
						}
						
					}else if (((Mushroom*)(*i))->getSTT() == READY)
					{
						tw<<13<<" ";
					}else{
						tw<<DEATH<<" ";
					}

				}else if ((*i)->getID() == MUSHROOMBIG)
				{
					if (((Mushroom*)(*i))->getSTT() == ACTIVE)
					{
						if (((Mushroom*)(*i))->isUpping)
						{
							tw<<11<<" ";
						}
						if (((Mushroom*)(*i))->isNormaling)
						{
							tw<<12<<" ";
						}
					}else if (((Mushroom*)(*i))->getSTT() == READY)
					{
						tw<<13<<" ";
					}else{
						tw<<DEATH<<" ";
					}

				}
				else{
					if ((*i)->getSTT() == BEFORE_DEATH || (*i)->getSTT() == DEATH)
					{
						tw<<DEATH<<" ";
					}else{
						tw<<(*i)->getSTT()<<" ";
					}
				}
			}
		}
		tw<<endl;
	}
}