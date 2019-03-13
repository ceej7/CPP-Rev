#pragma once
#include <iostream>
class ConstTest
{
public:
	int a = 1;
	int b = 2;
	void modify()
	{
		a = 2;
		b = 3;
	}
	int getA() const
	{
		return a;
	}
	void modify(int _a, int _b)
	{
		a = _a;
		b = _b;
	}
	ConstTest(const ConstTest& c)
	{
		std::cout << static_cast<void*>(this) << " copied" << std::endl;
	}
	ConstTest* operator=(const ConstTest& c)
	{
		std::cout << static_cast<void*>(this) << " assigned from" << (void*)(&c) << std::endl;
		return this;
	}
	ConstTest()
	{
		std::cout << static_cast<void*>(this) << " created" << std::endl;
	}
	~ConstTest()
	{
		std::cout << static_cast<void*>(this) << " released" << std::endl;
	}
};