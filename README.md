## Why have I done it?
Mostly as curiosity and an eagerness to make use of the amazing disassembler that is [Capstone](http://www.capstone-engine.org/).

## What does it do?
This a library that lets you hook any function of the calling conventions below marked.

By hooking, I mean essentially proxying its calls, that is, to intercept any call to a certain function so that instead of the code calling the original function it is now calling the function you chose to intercept it, you then choose whether it calls the original one or not.

I generally name the function that intercepts the call, _handler_.

## How does it work?
There's an amazing tutorial at the awesome channel [GuidedHacking](https://www.youtube.com/watch?v=jTl3MFVKSUM), it's fairly short when accounting for the huge knowledge bomb it has.

Although most of the logic is the same, rather than relying on the developer knowing how many bytes to rewrite and restore, I simply use the disassembler Capstone.

Stay tuned for my [Twitter](https://twitter.com/home) and [Blog](https://l3nsec.blog/) as I will (soon) explain how to write different _handlers_ for each of the calling conventions, as well as provide an explanation on how to compile and integrate this in your project.

## How to include/use this?

Download [Capstone's Libs](https://github.com/aquynh/capstone/releases) and this Library's .lib into your "Library Directories" inside VC++ Directories.

Also download the include files(.h) of both projects in your "Include Directories".

## Architectures
The target architecture of this library is Windows x86/x64, currently only developed for x86.
However it should work for Linux aswell(untested).

## Currently Tested
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
