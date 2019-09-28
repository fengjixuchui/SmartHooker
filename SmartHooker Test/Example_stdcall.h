#pragma once

#include <Windows.h>

// Defining the types of the function to hook
typedef int(__stdcall* MessageBox_t)(HWND, LPCSTR, LPCSTR, UINT);

// Declaring those types for the address of the original function
MessageBox_t MessageBox_o;

int WINAPI MessageBoxHandler(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	return MessageBox_o(0, "This is not safe!", lpCaption, 0);
}
