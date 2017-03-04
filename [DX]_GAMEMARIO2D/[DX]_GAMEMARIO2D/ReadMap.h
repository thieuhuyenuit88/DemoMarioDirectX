#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>
#include "tObj.h"

using namespace std;

class ReadMap{
private:
	static ReadMap* instance;
public:
	ReadMap(void);
	~ReadMap(void);

	static ReadMap* getReadMap();

	int basicDigital[6];
	map<string, vector<tObj*>> mapData;

	int digitalGameSaved[10];
	map<string, vector<tObj*>> savedData;

	void ReadFile(int _level){
		string strBuffer;
		strBuffer.empty();

		vector<string> listStringData;
		listStringData = vector<string>();
		
		ifstream inFile;

		char fileName[30];
		sprintf(fileName, "data//Map//level%d.txt", _level);
		inFile.open(fileName);

		int mapHeight;
		

		if (getline(inFile, strBuffer))
		{
			Split(strBuffer, listStringData, ' ');
			for (int i = 0; i < 6; i++)
			{
				basicDigital[i] = StringToInt(listStringData[i]);
			}
		}
		
		mapHeight = basicDigital[3];
		int countRow = 0;
		while(countRow < mapHeight){
			getline(inFile, strBuffer);
			countRow++;
		}

		while (!inFile.eof())
		{
			getline(inFile, strBuffer);
			Split(strBuffer, listStringData, ' ');
			ProcessDataToMap(listStringData);
		}

		inFile.close();
	}

	int ReadFile(){
		string strBuffer;
		strBuffer.empty();

		vector<string> listStringData;
		listStringData = vector<string>();

		ifstream inFile;

		char fileName[30];
		sprintf(fileName, "data//Save//gameSaved.txt");
		inFile.open(fileName);

		if (getline(inFile, strBuffer))
		{
			Split(strBuffer, listStringData, ' ');
			for (int i = 0; i < 10; i++)
			{
				digitalGameSaved[i] = StringToInt(listStringData[i]);
			}
		}else{
			return 0;
		}

		while (!inFile.eof())
		{
			getline(inFile, strBuffer);
			Split(strBuffer, listStringData, ' ');
			ProcessSavedToMap(listStringData);
		}

		inFile.close();

		return 1;
	}

	unsigned int Split(const string &txt, std::vector<std::string> &strs, char ch)
	{
		unsigned int pos = txt.find( ch );
		unsigned int initialPos = 0;
		strs.clear();

		// Decompose statement
		while( pos != std::string::npos ) {
			strs.push_back( txt.substr( initialPos, pos - initialPos) );
			initialPos = pos + 1;

			pos = txt.find( ch, initialPos );
		}

		// Add the last one
		strs.push_back( txt.substr( initialPos, min( pos, txt.size() ) - initialPos) );

		return strs.size();
	}

	int StringToInt(const string &str){
		int result;
		stringstream convert(str);
		return convert >> result ?  result : 0; 
	}

	void ProcessSavedToMap(vector<string> &_listDataString){
		string key;

		vector<tObj*> dataObject;
		dataObject = vector<tObj*>();

		int numOfObj;
		numOfObj = (_listDataString.size() - 1) / 4;

		key = _listDataString[0];

		int count = 0;
		while(count < numOfObj){
			int tID = StringToInt(_listDataString[count*4+ 1]);
			int tX = StringToInt(_listDataString[count*4 + 2]);
			int tY = StringToInt(_listDataString[count*4 + 3]);
			int tSTT = StringToInt(_listDataString[count*4 + 4]);
			dataObject.push_back(new tObj(tID, tX, tY, tSTT));
			count++;
		}

		savedData[key] = dataObject;

		dataObject.clear();
		vector<tObj*>().swap(dataObject);
	}

	void ProcessDataToMap(vector<string> &_listDataString){
		string key;
		
		vector<tObj*> dataObject;
		dataObject = vector<tObj*>();

		int numOfObj;
		numOfObj = (_listDataString.size() - 1)/3;

		key = _listDataString[0];

		int count = 0;
		while(count < numOfObj){
			int tID = StringToInt(_listDataString[count*3 + 1]);
			int tX = StringToInt(_listDataString[count*3 + 2]);
			int tY = StringToInt(_listDataString[count*3 + 3]);
			dataObject.push_back(new tObj(tID, tX, tY));
			count++;
		}

		mapData[key] = dataObject;

		dataObject.clear();
		vector<tObj*>().swap(dataObject);
	}
};