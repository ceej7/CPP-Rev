#include <iostream>
#include <iomanip>
#include <bitset>
#include "addA.h"
#include "addB.h"
#include "constants.h"
#include "RandGen.h"
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



	system("pause");
	return 0;
}
