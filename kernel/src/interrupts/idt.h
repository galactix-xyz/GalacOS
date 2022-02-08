#pragma once
#include <stdint.h>

struct IDTDescEntry
{
	uint16_t offset0;
	uint16_t selector;

	uint8_t ist;
	uint8_t type_attr;
	
	uint16_t offset1;

	uint32_t offset2;
	uint32_t ignore;
};

struct IDTR
{
	uint16_t Limit;
	uint64_t Offsetl
}__attribute__((packed));
