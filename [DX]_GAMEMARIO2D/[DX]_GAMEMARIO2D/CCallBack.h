#pragma once
#include <stdio.h>
#include "CLog.h"

class VCCallBack{
public:
	virtual void Execute(int _param) const = 0;
};

template<class cInstance>
class CCallBack: public VCCallBack{
public:
	typedef void (cInstance::*tFunction)(int);

	// constructor
	CCallBack(){
		pFunction = NULL;
	}

	virtual void Execute(int _param) const{
		if (pFunction) {
			(instance->*pFunction)(_param);
		}else{
			Clog::getClogInstance()->outLog("ERROR: the callback function has hot been defined!!!");
		}
	}

	void SetCallBack(cInstance *cInstancePointer,
		tFunction pFunctionPointer){
			instance = cInstancePointer;
			pFunction = pFunctionPointer;
	}
private:
	cInstance *instance;
	tFunction pFunction;
};

//class CCallBack: public VCCallBack {
//public:
//	typedef void (*tFunction)(int);
//	CCallBack(){
//		pFunction = NULL;
//	}
//
//	void SetCallBack(tFunction pFunctionPointer){
//		pFunction = pFunctionPointer;
//	}
//
//	virtual void Execute(int _param) const{
//		pFunction(_param);
//	}
//private:
//	tFunction pFunction;
//};
