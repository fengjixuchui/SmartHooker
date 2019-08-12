#include "Hooker.h"

#include <DbgHelp.h>

#include <capstone.h>

/**
* Returns what size of instructions is needed to be restored and also allocating which instructions(in the params).
*/
size_t Hooker::get_size_needed(PBYTE addy, DWORD base, DWORD hook_bytes_needed, std::vector<BYTE>& instructions)
{
	csh handle;
	cs_insn *insn;
	size_t size_of_instructions = 0;
	std::vector<uint8_t> inst_bytes_list;

	if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK)
		return CS_ERR_CSH;

	const size_t count = cs_disasm(handle, addy, hook_bytes_needed + (hook_bytes_needed % 15), base, 0, &insn);

	int last_sum = 0;

	if (count > 0) {
		for (size_t j = 0; j < count; j++) {
			// iterate until we see get space for our code
			if ((size_of_instructions = insn[j].size + last_sum) >= hook_bytes_needed)
			{
				int inst_index = 0;
				for (size_t i = 0; i <= j; i++)
				{
					for (int z = 0; z < insn[i].size;z++)
						inst_bytes_list.push_back(insn[i].bytes[z]);
				}

				break;
			}

			last_sum += insn[j].size;
		}

		for (size_t i = 0; i < inst_bytes_list.size(); i++) {
			instructions.push_back(inst_bytes_list[i]);
		}

		cs_free(insn, count);
	}
	else {
		return CS_ERR_MEMSETUP;
	}

	cs_close(&handle);

	return size_of_instructions;
}

/**
 * Returns a pointer to the hooked function.
 */
LPVOID Hooker::Detour(LPVOID to_hook, LPVOID func_handler) {
	std::vector<BYTE> inst;
	const size_t len = get_size_needed((PBYTE)to_hook, (DWORD)to_hook, JMP_TO_HOOK_MIN_SIZE, inst);

	DWORD dwOld;
	VirtualProtect(to_hook, len, PAGE_EXECUTE_READWRITE, &dwOld); // changing the permissions of the function to be able to rewrite first instructions by jumping to handler

	memset(to_hook, 0x90, len);

	DWORD relativeAddress = (DWORD)func_handler - (DWORD)to_hook - JMP_TO_HOOK_MIN_SIZE; // the jump we're going to do is relative, so we need to get the relative "distance"
	
	*(PBYTE)(to_hook) = 0xE9; // JMP opcode https://c9x.me/x86/html/file_module_x86_id_147.html
	*(DWORD*)((DWORD)to_hook + 1) = relativeAddress; // we write the relative address after the opcode, writing directly as DWORD to not have to deal with little endian

	VirtualProtect(to_hook, len, dwOld, &dwOld); // restore the old protection it had

	PBYTE trampoline = (PBYTE)VirtualAlloc(NULL, len + JMP_TO_HOOK_MIN_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE); // allocate our "trampoline" which is: restored bytes and a jmp to hooked

	if (trampoline == NULL)
		return NULL;

	for (size_t i = 0; i < len; i++) // copies all original instructions to the trampoline
		*(trampoline+i) = inst[i];

	*(trampoline+len) = 0xE9; // write the JMP opcode to trampoline

	relativeAddress = (DWORD)to_hook - (DWORD)trampoline - len; // get the relative address to the original code

	*(DWORD*)(trampoline + len + 1) = relativeAddress;

	VirtualProtect(trampoline, len + JMP_TO_HOOK_MIN_SIZE, PAGE_EXECUTE, &dwOld); // we want to make the trampoline have the normal permissions for code

	return trampoline;
}
