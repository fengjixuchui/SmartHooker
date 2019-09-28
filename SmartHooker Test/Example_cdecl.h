#pragma once

#include <stdio.h>

// Defining the types of the function to hook
typedef int(__cdecl* hooked_t)(int, unsigned char, short);

// Declaring those types for the address of the original function
hooked_t hooked_o;

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
