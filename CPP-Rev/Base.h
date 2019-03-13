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