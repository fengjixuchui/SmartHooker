#pragma once

// Example class to test thiscall functions
class ExampleClass
{
private:
	double money;
public:
	ExampleClass::ExampleClass();
	ExampleClass::ExampleClass(double money);
	double ExampleClass::GetSalary(double money);
	double ExampleClass::GetMoney();
};
