#include "Hooker.h"
#include "ExampleClass.h"

// Defining the types of the functions to hook
typedef int(__cdecl* hooked_t)(int, unsigned char, short);
typedef int(__stdcall* MessageBox_t)(HWND, LPCSTR, LPCSTR, UINT);
typedef double(__thiscall* GetSalary_t)(double);
typedef bool(__fastcall* IsKeyPressed_t)(UCHAR);

// Declaring those types for the address of the original functions
hooked_t hooked_o;
MessageBox_t MessageBox_o;
GetSalary_t GetSalary_o;
IsKeyPressed_t IsKeyPressed_o;

/**
 * This will print the args if the a1 is < 500 otherwise will just call the original
 */
int __cdecl victim_handler(int a1, unsigned char b1, short c1)
{
	return (a1 < 500) ? printf("%i %i %hi\n", a1, (int)b1, c1) : hooked_o(a1, b1, c1);
}

int __cdecl victim_method(int a1, unsigned char b1, short c1)
{
	a1 += 20;

	b1 -= 20;

	c1 += 666;

	return printf("%i %i %hi\n", a1, (int)b1, c1);
}

int WINAPI MessageBoxHandler(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	return MessageBox_o(0, "This is not safe!", lpCaption, 0);
}

bool __fastcall IsKeyPressed(UCHAR vk)
{
	return GetAsyncKeyState(vk);
}

bool __fastcall IsKeyPressedHandler(UCHAR vk)
{
	if (vk == VK_END) return 1;

	return IsKeyPressed_o(vk);
}

// We're handling thiscall as stdcall by getting the this pointer with inline assembly
double __stdcall GetSalaryHandler(double money)
{
	ExampleClass* example;

	__asm {
		mov dword ptr[example], ecx;
	}

	return example->GetMoney() + (GetSalary_o(money) * 5);
}

int main()
{
	system("color 4 && title SmartHooker Test");

	/* Recommend you to read: https://en.wikipedia.org/wiki/X86_calling_conventions */

	printf("Testing cdecl:\n\n");

	printf("Got %i characters\n", victim_method(200, 120, 600));

	hooked_o = (hooked_t)Hooker::Detour(victim_method, victim_handler);

	printf("Got %i characters\n", victim_method(200, 120, 600));

	printf("Got %i characters\n\n", victim_method(500, 120, 600));

	printf("Press enter to continue to stdcall.");

	getchar();

	printf("Testing stdcall:\n\n");

	MessageBoxA(0, "This is safe", "Safety Test", 0);

	MessageBox_o = (MessageBox_t)Hooker::Detour(MessageBoxA, MessageBoxHandler);

	MessageBoxA(0, "This is safe", "Safety Test", 0);

	printf("Press enter to continue to fastcall.");

	getchar();

	printf("Testing fastcall:\n\n");

	printf("Is END pressed: %s\n", IsKeyPressed(VK_END) ? "yes" : "no");

	IsKeyPressed_o = (IsKeyPressed_t)Hooker::Detour(IsKeyPressed, IsKeyPressedHandler);

	printf("Is END pressed: %s\n\n", IsKeyPressed(VK_END) ? "yes" : "no");
	printf("Is HOME pressed: %s\n\n", IsKeyPressed(VK_HOME) ? "yes" : "no");

	printf("Press enter to continue to thiscall.");

	getchar();

	printf("Testing thiscall:\n\n");

	ExampleClass first(500);
	ExampleClass second;

	printf("First's got his salary, his balance now is: %.2f\n", first.GetSalary(470));

	double(__thiscall ExampleClass:: * memberFunc)(double) = &ExampleClass::GetSalary;
	GetSalary_o = (GetSalary_t)Hooker::Detour((LPVOID&)memberFunc, GetSalaryHandler);

	printf("Second's got his salary, his balance now is: %.2f\n", second.GetSalary(1200.0));

	getchar();
}