#pragma once

// Defining the types of the function to hook
typedef bool(__fastcall* IsKeyPressed_t)(UCHAR);

// Declaring those types for the address of the original function
IsKeyPressed_t IsKeyPressed_o;

bool __fastcall IsKeyPressed(UCHAR vk)
{
	return GetAsyncKeyState(vk);
}

bool __fastcall IsKeyPressedHandler(UCHAR vk)
{
	if (vk == VK_END) return 1;

	return IsKeyPressed_o(vk);
}
