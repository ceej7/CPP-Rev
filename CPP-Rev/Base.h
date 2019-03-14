#pragma once
#include <iostream>
class Base
{
private:
	int m_id;
public:
	Base(int id = 0)
		: m_id(id)
	{
	}

	virtual int getId() const {
		std::cout << "Base" << std::endl;
		return m_id; }
	friend std::ostream& operator<<(std::ostream& out, const Base &base)
	{
		return out << base.m_id<<std::endl;
	}
};

class Derived : public Base
{
public:
	double m_cost;

	Derived(double cost = 0.0)
		: m_cost(cost)
	{
		
	}

	double getCost() const { return m_cost; }
	int getId() const { 
		std::cout << "Derived" << std::endl;
		return m_cost; }
};
class A_Excep
{
private:
	int m_x;
public:
	A_Excep(int x) : m_x(x)
	{
		if (x <= 0) {

			throw 1;
		}
	}
};

class B_Excep : public A_Excep
{
public:
	B_Excep(int x) try : A_Excep(x) // note addition of try keyword here
	{
		throw 2;
	}
	catch (int e) // note this is at same level of indentation as the function itself
	{
		// Exceptions from member initializer list or constructor body are caught here

		std::cerr << "Construction of "<<e<<" failed\n";

		// If an exception isn't explicitly thrown here, the current exception will be implicitly rethrown
	}
};