#include "CLog.h"
Clog* Clog::instance = NULL;

Clog::Clog(void){
	szBuf = new char[256];
}

Clog::~Clog(void){
	szBuf = NULL;
}