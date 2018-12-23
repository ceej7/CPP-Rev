#include <iostream>
#include "addA.h"
#include "addB.h"

//call stack issue
void CallC()
{
	std::cout << "C called" << std::endl;
}

void CallB()
{
	std::cout << "B called" << std::endl;
	CallC();
}

void CallA()
{
	CallB();
	CallC();
}


int main()
{
	////namespace issue
	//std::cout << "The sum of 3 and 4 is: " << A::add(3, 4) << std::endl;
	//std::cout << "The sum of 3 and 4 is: " << B::add(3, 4) << std::endl;
	//system("pause");
	//return 0;
	
	//call stack issue
	CallA();

}