#include <iostream>
#include "add.cpp"
int A::add(int x, int y); // needed so main.cpp knows that add() is a function declared elsewhere

int main()
{
	std::cout << "The sum of 3 and 4 is: " << A::add(3, 4) << std::endl;
	return 0;
}