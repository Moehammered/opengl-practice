#pragma once

#include <iostream>

void printAddress(void*& ptr);
void printAddress(float*& ptr);
bool isPointerNull(void*& ptr);
bool isSharedPointer(void*& ptr1, void*& ptr2);

void printAddress(float*& ptr)
{
	void* casted = (void*)ptr;
	printAddress(casted);
}

void printAddress(void*& ptr)
{
	std::cout << "Pointer Address: 0x" << ptr << std::endl;
}

bool isPointerNull(void*& ptr)
{
	return ptr == nullptr;
}

bool isSharedPointer(void*& ptr1, void *&ptr2)
{
	return ptr1 == ptr2;
}