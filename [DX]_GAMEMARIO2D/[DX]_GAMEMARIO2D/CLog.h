#pragma once
#include <Windows.h>
#include <stdio.h>
class Clog{
private:
	static Clog* instance;
	char* szBuf;
public:
	Clog(void);
	~Clog(void);

	static Clog* getClogInstance(){
		if (instance == NULL)
		{
			instance = new Clog();
		}
		return instance;
	}

	void outLog(const char* str, ...){
		OutputDebugString("ClogGameMario: ");
		
		va_list argList;

		va_start(argList, str);
		vsnprintf(szBuf, 256, str, argList);
		va_end(argList);

		OutputDebugString(szBuf);
		OutputDebugString("\n");
	}
};