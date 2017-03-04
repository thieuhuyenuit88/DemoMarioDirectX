#pragma once
#include "MyObject.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Global.h"
#include <vector>
#include <string>
#include "tObj.h"

using namespace std;

class QuadTreeNode{
private:
	vector<MyObject*> *contents;

	vector<StaticObject*>* contentsStatic;
	vector<DynamicObject*>* contentsDynamic;

	vector<QuadTreeNode*> *nodeChild;
	CRECT bounds;
public:
	QuadTreeNode(void);
	QuadTreeNode(CRECT _bounds, string _strID);
	~QuadTreeNode(void);

	string strNodeID;

	CRECT getBounds(){
		return bounds;
	}

	void setBounds(CRECT _bounds){
		bounds = _bounds;
	}

	//get contents static
	vector<StaticObject*>* getContentsStatic(){
		return contentsStatic;
	}

	//get contents of this node with new list then clear old list
	vector<StaticObject*>* getContentsStaticEx(){
		vector<StaticObject*> *result = new std::vector<StaticObject*>();
		result->insert(result->begin(), contentsStatic->begin(), contentsStatic->end());

		contentsStatic->clear();
		return result;
	}

	//get contents dynamic
	vector<DynamicObject*>* getContentsDynamic(){
		return contentsDynamic;
	}

	//get contents of this node with new list then clear old list
	vector<DynamicObject*>* getContentsDynamicEx(){
		vector<DynamicObject*> *result = new std::vector<DynamicObject*>();
		result->insert(result->begin(), contentsDynamic->begin(), contentsDynamic->end());

		contentsDynamic->clear();
		return result;
	}

	//get contents
	vector<MyObject*>* getContents(){
		return contents;
	}

	//get contents of this node with new list then clear old list
	vector<MyObject*>* getContentsEx(){
		vector<MyObject*> *result = new std::vector<MyObject*>();
		result->insert(result->begin(), contents->begin(), contents->end());

		contents->clear();
		return result;
	}

	//create all nodes for child
	void CreateSubNodes();

	//Create quadtree
	void CreateQuadTree();

	//get contents of all child of this node
	vector<MyObject*>* getSubTreeContents();

	//get contents of all child of this node
	vector<DynamicObject*>* getSubTreeContentsDynamic();

	//get contents of all child of this node
	vector<StaticObject*>* getSubTreeContentsStatic();

	//add object into tree
	void Insert(MyObject* obj);

	//add object into tree
	void Insert(DynamicObject* obj);

	//add object into tree
	void Insert(StaticObject* obj);

	//query list objects from tree with an area
	vector<MyObject*>* Query(CRECT area);

	//query list objects from tree with an area
	vector<DynamicObject*>* QueryDN(CRECT area);

	//query list objects from tree with an area
	vector<StaticObject*>* QueryST(CRECT area);
	
	//get node follow id
	QuadTreeNode* getNodeChildWithID(string _strID);

	//get dest tree node
	QuadTreeNode* getDestTreeNode(MyObject* obj);

	//count number object
	int countObject();

	//check node empty
	bool isEmpty();

	int countObjectDN(){
		int result = 0;
		result += contentsDynamic->size();
		if (nodeChild->size() > 0)
		{
			for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
			{
				result += (*i)->countObjectDN();
			}
		}
		return result;
	}

	int countObjectST(){
		int result = 0;
		result += contentsStatic->size();
		if (nodeChild->size() > 0)
		{
			for (vector<QuadTreeNode*>::iterator i = nodeChild->begin(); i != nodeChild->end(); i++)
			{
				result += (*i)->countObjectST();
			}
		}
		return result;
	}

	bool isEmptyDN(){
		if (this->countObjectDN() > 0)
		{
			return false;
		}
		return true;
	}

	bool isEmptyST(){
		if (this->countObjectST() > 0)
		{
			return false;
		}
		return true;
	}

	void SaveQuadTree(ofstream &tw);

	//DeserializeObject
	void DeserializeObjectToQuadTree(const string &_strNodeID, vector<tObj*> &_listObjects);
};