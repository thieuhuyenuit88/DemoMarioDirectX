#pragma once
#include "QuadTreeNode.h"
#include "MyObject.h"

using namespace std;
class QuadTree{
	QuadTreeNode* rootTree;
	CRECT bounds;
public:
	QuadTree(CRECT _bounds);
	~QuadTree(void);

	QuadTreeNode* getRootTree(){
		return rootTree;
	}

	CRECT getBoundTree(){
		return bounds;
	}

	int countObj(){
		return rootTree->countObject();
	}

	void CreateQuadTree();

	void Insert(MyObject* obj);
	void Insert(DynamicObject* obj);
	void Insert(StaticObject* obj);

	vector<MyObject*>* Query(CRECT area);
	vector<DynamicObject*>* QueryDN(CRECT area);
	vector<StaticObject*>* QueryST(CRECT area);

	void SaveQuadTree(ofstream &tw);

	QuadTreeNode* GetQuadTreeNodeWithID(string _strID);
};