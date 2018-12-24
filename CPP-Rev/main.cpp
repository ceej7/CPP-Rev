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
	
	
	////call stack issue
	//CallA();

	////Data type char issue
	//std::cout << sizeof(wchar_t) << std::endl;
	//std::cout << sizeof(char16_t) << std::endl;
	//std::cout << sizeof(char32_t) << std::endl;

	//uniform initial try
	//int nValue0{ 0 };
	//int nValue1{ 1 };
	//int nValueNar{ 4.5 };//narrow converting

	system("pause");
	return 0;
}