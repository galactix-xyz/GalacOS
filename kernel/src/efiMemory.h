#pragma once
#include <stdint.h>

struct EFI_MEMORY_DESCRIPTOR
{
	uint32_t type;
	void* physAddr;
	void* virtAdd;
	uint64_t numPages;
	uint64_t attribs;
};

extern const char* EFI_MEMORY_TYPE_STRINGS[];