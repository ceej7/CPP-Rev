#pragma once
#include <iostream>
template <class T>
class Temp1 {
public:
	T i;
	Temp1()
	{

	}
	~Temp1()
	{

	}

};
template <>
class Temp1<double> {
public:
	double i;
	Temp1()
	{
		std::cout << "it's double" << std::endl;
	}
	~Temp1()
	{

	}

};

template<typename T>
void tempFunction(T i)
{
	std::cout << i << std::endl;
}
template<>
void tempFunction(double i)
{
	std::cout <<"double: " <<i << std::endl;
}