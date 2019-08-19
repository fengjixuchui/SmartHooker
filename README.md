## Why have I done it?
Mostly as curiosity and an eagerness to make use of the amazing disassembler that is [Capstone](http://www.capstone-engine.org/).

## What does it do?
This a library that lets you hook any function of the calling conventions below marked.

By hooking, I mean essentially proxying its calls, that is, to intercept any call to a certain function so that instead of the code calling the original function it is now calling the function you chose to intercept it, you then choose whether it calls the original one or not.

I generally name the function that intercepts the call, _handler_.

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

## Capstone Copyright Notice
This is the software license for Capstone disassembly framework.
Capstone has been designed & implemented by Nguyen Anh Quynh <aquynh@gmail.com>

See http://www.capstone-engine.org for further information.

Copyright (c) 2013, COSEINC.
All rights reserved.
