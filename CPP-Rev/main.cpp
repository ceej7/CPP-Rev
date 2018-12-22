#include <iostream>
#include "addA.h"
#include "addB.h"
int main()
{
	std::cout << "The sum of 3 and 4 is: " << A::add(3, 4) << std::endl;
	std::cout << "The sum of 3 and 4 is: " << B::add(3, 4) << std::endl;
	system("pause");
	return 0;
}