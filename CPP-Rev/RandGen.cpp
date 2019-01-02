#include "RandGen.h"
#include <iostream>
#include <stdlib.h>//rand & srand
#include <ctime>//std::time
void RandGen::testRand()
{
	srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int count = 1; count <= 100; ++count)
	{
		std::cout << rand() << "\t";

		// If we've printed 5 numbers, start a new row
		if (count % 5 == 0)
			std::cout << "\n";
	}

}

void  RandGen::setRoot()
{
	if (!isInI)
		srand(static_cast<unsigned int>(std::time(nullptr)));
	isInI = true;
}
int  RandGen::getRand()
{
	if (!isInI)
		setRoot();
	isInI = true;
	return rand();
}
int RandGen::getRand(int _min, int _max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);//*srand belong to [0,1) inclusive - exclusive
	return _min + static_cast<int>(_max - _min + 1)*(std::rand()*fraction);
}