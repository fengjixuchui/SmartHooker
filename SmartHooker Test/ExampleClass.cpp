#include "ExampleClass.h"

ExampleClass::ExampleClass()
{
	money = 0;
}

ExampleClass::ExampleClass(double money)
{
	this->money = money;
}

double ExampleClass::GetSalary(double money)
{
	return this->money += money;
}

double ExampleClass::GetMoney()
{
	return money;
}
