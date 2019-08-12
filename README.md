## Why have I done it?
Mostly as curiosity and an eagerness to make use of the amazing disassembler that is [Capstone](http://www.capstone-engine.org/).

To accomplish this I'm using capstone, a disassembly framework.

## How does it work?
Stay tuned for my [Twitter](https://twitter.com/home) and [Blog](https://l3nsec.blog/) as I will explain in detail how hooking works, what calling conventions look like, what is a detour and the logic behind this library.

## Architectures
The target architecture of this library is Windows x86/x64, currently only developed for x86.
However it should work for Linux aswell(untested).

## Current Tested
x86 Detour Hook with Trampoline(JMP Relative) calling conventions:
- cdecl ✔️
- stdcall ✔️
- fastcall ✔️
- thiscall ✔️
- vectorcall ❓

## Next Steps
* Detour Hook without Trampoline
* Remove Detour Hook
* Push Ret Method
* Indirect Jump Method
* Call Method
