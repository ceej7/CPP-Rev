#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstring>
#include <vector>
#include <cstdarg>
#include "addA.h"
#include "addB.h"
#include "constants.h"
#include "RandGen.h"
#include "Auto_ptr.h"
#include "ConstTest.h"
#include "Base.h"
#include "TemplateSample.h"
#define __STDC_WANT_LIB_EXT1__ 1

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

auto autotest(int a, int b) -> int
{
	return a + b;
}

enum Animal
{
	ANIMAL_CAT = -3,
	ANIMAL_DOG, // assigned -2
	ANIMAL_PIG, // assigned -1
	ANIMAL_HORSE = 5,
	ANIMAL_GIRAFFE = 5, // shares same value as ANIMAL_HORSE
	ANIMAL_CHICKEN // assigned 6
};

char getOperator()
{
	while (true) // Loop until user enters a valid input
	{
		std::cout << "Enter one of the following: +, -, *, or /: ";
		char op;
		std::cin >> op;
		std::cin.ignore(32767, '\n');
		// Check whether the user entered meaningful input
		if (op == '+' || op == '-' || op == '*' || op == '/')
			return op; // return it to the caller
		else // otherwise tell the user what went wrong
			std::cout << "Oops, that input is invalid.  Please try again.\n";
	} // and try again
}

double getDouble()
{
	while (true) // Loop until user enters a valid input
	{
		std::cout << "Enter a double value: ";
		double x;
		std::cin >> x;

		// Check for failed extraction
		if (std::cin.fail()) // has a previous extraction failed?
		{
			// yep, so let's handle the failure
			std::cin.clear(); // put us back in 'normal' operation mode
			std::cin.ignore(32767, '\n'); // and remove the bad input
			std::cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else
		{
			std::cin.ignore(32767, '\n'); // remove any extraneous input

			// the user can't enter a meaningless double value, so we don't need to worry about validating that
			return x;
		}
	}
}

void printResult(double x, char op, double y)
{
	if (op == '+')
		std::cout << x << " + " << y << " is " << x + y << '\n';
	else if (op == '-')
		std::cout << x << " - " << y << " is " << x - y << '\n';
	else if (op == '*')
		std::cout << x << " * " << y << " is " << x * y << '\n';
	else if (op == '/')
		std::cout << x << " / " << y << " is " << x / y << '\n';
	else // Being robust means handling unexpected parameters as well, even though getOperator() guarantees op is valid in this particular program
		std::cout << "Something went wrong: printResult() got an invalid operator.";

}

namespace IndexSpace
{
	enum indexEnum
	{
		OneIndex,
		TwoIndex,
		ThreeIndex,
		MaxIndex
	};
}

ConstTest returnbyVal()
{
	ConstTest c;
	return c;
}

void foo(int n)
{
	int c = 0;
	if (n == 0) return;
	else
	{
		std::cout <<"c: "<<&c<<"        "<< (void *)foo << std::endl;
		foo(n - 1);
	}
}

// Note our user-defined comparison is the third parameter
void selectionSort(int *array, int size, bool(*comparisonFcn)(int, int))
{
	// Step through each element of the array
	for (int startIndex = 0; startIndex < size; ++startIndex)
	{
		// bestIndex is the index of the smallest/largest element we've encountered so far.
		int bestIndex = startIndex;

		// Look for smallest/largest element remaining in the array (starting at startIndex+1)
		for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
		{
			// If the current element is smaller/larger than our previously found smallest
			if ((*comparisonFcn)(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
				// This is the new smallest/largest number for this iteration
				bestIndex = currentIndex;
		}

		// Swap our start element with our smallest/largest element
		std::swap(array[startIndex], array[bestIndex]);
	}
}

// Here is a comparison function that sorts in ascending order
// (Note: it's exactly the same as the previous ascending() function)
bool ascending(int x, int y)
{
	return x > y; // swap if the first element is greater than the second
}

// Here is a comparison function that sorts in descending order
bool descending(int x, int y)
{
	return x < y; // swap if the second element is greater than the first
}

// This function prints out the values in the array
void printArray(int *array, int size)
{
	for (int index = 0; index < size; ++index)
		std::cout << array[index] << " ";
	std::cout << '\n';
}

double findAverage(int count, ...)
{
	double sum = 0;

	// We access the ellipsis through a va_list, so let's declare one
	va_list list;

	// We initialize the va_list using va_start.  The first parameter is
	// the list to initialize.  The second parameter is the last non-ellipsis
	// parameter.
	va_start(list, count);

	// Loop through all the ellipsis arguments
	for (int a = 0; a < count; ++a)
		// We use va_arg to get parameters out of our ellipsis
		// The first parameter is the va_list we're using
		// The second parameter is the type of the parameter
		sum += va_arg(list, int);

	// Cleanup the va_list when we're done.
	va_end(list);

	return sum / count;
}

Auto_ptr4<Resource> generateResource()
{
	Auto_ptr4<Resource> res(new Resource);
	return res; // this return value will invoke the move constructor
}

Auto_ptr5<Resource> generateResource(Auto_ptr5<Resource> a)
{
	//Auto_ptr5<Resource> res(a); //compile error
	// deleted
	//return res; // this return value will invoke the move constructor
	return 0;
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

	//uniform initial tdry
	//int nValue0{ 0 };
	//int nValue1{ 1 };
	//int nValueNar{ 4.5 };//narrow converting

	////Round Issue
	//double d(0.1);
	//std::cout << d << std::endl; // use default cout precision of 6
	//std::cout << std::setprecision(17);
	//std::cout << d << std::endl;
	//double d2(0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1); // should equal 1.0
	//std::cout << d2 << std::endl;

	////char
	//char ch(97);
	//std::cout << ch << std::endl;
	//std::cout << static_cast<int>(ch) << std::endl;
	//std::cout << ch << std::endl;

	////bitset
	//// Define 8 separate bit flags (these can represent whatever you want)
	//const unsigned char option0 = 1 << 0; // 0000 0001 
	//const unsigned char option1 = 1 << 1; // 0000 0010
	//const unsigned char option2 = 1 << 2; // 0000 0100
	//const unsigned char option3 = 1 << 3; // 0000 1000
	//const unsigned char option4 = 1 << 4; // 0001 0000
	//const unsigned char option5 = 1 << 5; // 0010 0000
	//const unsigned char option6 = 1 << 6; // 0100 0000
	//const unsigned char option7 = 1 << 7; // 1000 0000

	//std::bitset<8> bits(option1 | option2); // start with option 1 and 2 turned on
	//std::bitset<8> morebits(0x3); // start with bit pattern 0000 0011
	//std::cout << bits << std::endl;
	//std::cout << morebits << std::endl;

	//const int option0 = 0;
	//const int option1 = 1;
	//const int option2 = 2;
	//const int option3 = 3;
	//const int option4 = 4;
	//const int option5 = 5;
	//const int option6 = 6;
	//const int option7 = 7;

	//std::bitset<8> bits(0x2); // we need 8 bits, start with bit pattern 0000 0010
	//bits.set(option4); // set bit 4 to 1 (now we have 0001 0010)
	//bits.flip(option5); // flip bit 5 (now we have 0011 0010) 0-1 and vice versa
	//bits.reset(option5); // set bit 5 back to 0 (now we have 0001 0010)

	//std::cout << "Bit 4 has value: " << bits.test(option4) << '\n';
	//std::cout << "Bit 5 has value: " << bits.test(option5) << '\n';
	//std::cout << "All the bits: " << bits << '\n';

	////An RGB color example
	//const uint32_t rBits = 0xFF000000;
	//const uint32_t gBits = 0x00FF0000;
	//const uint32_t bBits = 0x0000FF00;
	//const uint32_t aBits = 0x000000FF;
	//std::cout << "Plz enter a 32-bit RGBA color value in hexdecimal form(e.g. 7F8A1109): ";
	//uint32_t pixel;
	//std::cin >> std::hex >> pixel;
	//
	//std::cout << "R value is: " << static_cast<int>((pixel&rBits) >> 24) << std::endl;
	//std::cout << "G value is: " << static_cast<int>((pixel&gBits) >> 16) << std::endl;
	//std::cout << "B value is: " << static_cast<int>((pixel&bBits) >> 8 ) << std::endl;
	//std::cout << "A value is: " << static_cast<int>((pixel&aBits) >> 0 ) << std::endl;

	////contanst issue
	//std::cout << Constants::pi << std::endl;

	//enum classes
	//enum Color
	//{
	//	RED, // RED is placed in the same scope as Color
	//	BLUE
	//};

	//enum Fruit
	//{
	//	BANANA, // BANANA is placed in the same scope as Fruit
	//	APPLE
	//};
	//enum class FruitClass
	//{
	//	BANANA, // BANANA is placed in the same scope as Fruit
	//	APPLE
	//};

	//Color color = RED; // Color and RED can be accessed in the same scope (no prefix needed)
	//Fruit fruit = BANANA; // Fruit and BANANA can be accessed in the same scope (no prefix needed)

	//if (color == fruit) // The compiler will compare a and b as integers
	//	std::cout << "color and fruit are equal\n"; // and find they are equal!
	//else
	//	std::cout << "color and fruit are not equal\n";

	////auto issue
	//std::cout << autotest(1, 2) << std::endl;

	////Rand issue
	//RandGen randGen;
	//std::cout << randGen.getRand(1, 6) << std::endl;
	//std::cout << randGen.getRand(1, 6) << std::endl;
	//std::cout << randGen.getRand(1, 6) << std::endl;

	////validate error input
	//double x = getDouble();
	//char op = getOperator();
	//double y = getDouble();

	//printResult(x, op, y);

	//int ary[IndexSpace::MaxIndex];

	//char source[] = "Copy";
	//char dest[]="abcdefg"; // note that the length of dest is only 5 chars!
	//strcpy_s(dest, 8, source); // An runtime error will occur in debug mode
	//std::cout << dest;

	/*int value = 5;
	int &ref1 = value;
	std::cout << ref1 << std::endl;

	const int &ref2 = 6;
	std::cout << ref2 << std::endl;*/

	//int(*array1)[5] = new int[10][5];
	//
	//int **array2 = new int*[10]; // allocate an array of 10 int pointers ¡ª these are our rows
	//for (int count = 0; count < 10; ++count)
	//	array2[count] = new int[5];

	//const ConstTest ctest;
	//std::cout << ctest.getA() << std::endl;

	//ConstTest c;
	//c = returnbyVal();

	//int array[9] = { 3, 7, 9, 5, 6, 1, 8, 2, 4 };

	//// Sort the array in descending order using the descending() function
	//selectionSort(array, 9, descending);
	//printArray(array, 9);

	//// Sort the array in ascending order using the ascending() function
	//selectionSort(array, 9, ascending);
	//printArray(array, 9);
	//std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
	//std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';

	//{
	//	Auto_Ptr1<Resource> ptr(new Resource);
	//	ptr->sayHi();
	//}
	//{
	//	Auto_Ptr2<Resource> res1(new Resource);
	//	Auto_Ptr2<Resource> res2(new Resource); // Start as nullptr

	//	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	//	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	//	res2 = res1; // res2 assumes ownership, res1 is set to null

	//	std::cout << "Ownership transferred\n";

	//	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	//	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");
	//}
	// int &&a = 5;
	//std::cout << a << std::endl;
	//{
	//	Auto_ptr4<Resource> mainres;
	//	mainres = generateResource(); // this assignment will invoke the move assignment
	//
	//}
	
	//Base *ptr = new Derived();
	//ptr->getId();
	//Derived obj;
	//obj.getId();
	//system("PAUSE");

	//Temp1<double> dt;
	//Temp1<int> it;

	//tempFunction(1);
	//tempFunction(1.1);

	//try {
	//	B_Excep(-1);
	//	}
	//catch (...)
	//{
	//	std::cout << "opps" << std::endl;
	//}

	//std::unique_ptr<Base[]> f1 = std::make_unique<Base[]>(4);
	//std::cout << f1[0] << f1[1] << f1[2] << f1[3];

	
}
