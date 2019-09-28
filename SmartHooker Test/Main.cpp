#include "Hooker.h"
#include "Example_cdecl.h"
#include "Example_stdcall.h"
#include "Example_fastcall.h"
#include "ExampleClass_thiscall.h"
#include "Example_thiscall.h"

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