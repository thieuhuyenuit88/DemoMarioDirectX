#pragma once
#include <ctime>
#include <cstdlib> 

class CRandom{
public:
	static int RandomBetweenInt(int min, int max){
		srand(time(NULL));
		return rand()%(max-min + 1) + min;
	}

	static int RandomBetweenIntRemoveBias(int min, int max){
		//srand(time(NULL));
		int n = max - min + 1;
		int remainder = RAND_MAX % n;
		int x;
		do{
			x = rand();
		}while (x >= RAND_MAX - remainder);
		return min + x % n;
	}
};