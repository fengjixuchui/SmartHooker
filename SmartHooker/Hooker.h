#pragma once

#include <Windows.h>
#include <vector>

#define JMP_TO_HOOK_MIN_SIZE 5

class __declspec(dllexport) Hooker
{
public:
	/**
	* Returns what size of instructions is needed to be restored and also allocating which instructions(in the params).
	*/
	static size_t Hooker::get_size_needed(PBYTE addy, DWORD base, DWORD hook_bytes_needed, std::vector<BYTE>& instructions);

	/**
	 * Returns a pointer to the hooked function.
	 */
	static LPVOID Hooker::Detour(LPVOID to_hook, LPVOID func_handler);
};

