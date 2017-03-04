#include "QuadTree.h"

QuadTree::QuadTree(CRECT _bounds){
	bounds =_bounds;
	rootTree = new QuadTreeNode(_bounds, "1");
	//rootTree->strNodeID = "1";
}

QuadTree::~QuadTree(void){
	if (rootTree != NULL)
	{
		delete rootTree;
	}
}

void QuadTree::CreateQuadTree(){
	rootTree->CreateQuadTree();
}

void QuadTree::Insert(MyObject* obj){
	LEVELNODE = 1;
	rootTree->Insert(obj);
}

void QuadTree::Insert(DynamicObject* obj){
	LEVELNODE = 1;
	rootTree->Insert(obj);
}

void QuadTree::Insert(StaticObject* obj){
	LEVELNODE = 1;
	rootTree->Insert(obj);
}

vector<MyObject*>* QuadTree::Query(CRECT area){
	return rootTree->Query(area);
}

vector<DynamicObject*>* QuadTree::QueryDN(CRECT area){
	return rootTree->QueryDN(area);
}

vector<StaticObject*>* QuadTree::QueryST(CRECT area){
	return rootTree->QueryST(area);
}

void QuadTree::SaveQuadTree(ofstream &tw){
	rootTree->SaveQuadTree(tw);
}

QuadTreeNode* QuadTree::GetQuadTreeNodeWithID(string _strID){
	return rootTree->getNodeChildWithID(_strID);
}

