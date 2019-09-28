#pragma once

#include "ExampleClass_thiscall.h"

// Defining the types of the function to hook
typedef double(__thiscall* GetSalary_t)(double);

// Declaring those types for the address of the original function
GetSalary_t GetSalary_o;

// We're handling thiscall as stdcall by getting the this pointer with inline assembly
// There are at least 2 others of doing this, one is creating a "dummy" class that points
// to the real class (via its address) and implementing a function handler
// Another way is doing fastcall and ignoring the second parameter
// the first is the this pointer
double __stdcall GetSalaryHandler(double money)
{
	ExampleClass* example;

	__asm {
		mov dword ptr[example], ecx;
	}

	return example->GetMoney() + (GetSalary_o(money) * 5);
}
