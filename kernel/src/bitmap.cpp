#include "bitmap.h"

bool Bitmap::operator[](uint64_t index) {
	uint64_t byteIndex = index / 8;
	uint8_t bitIndex = index % 8;
	uint8_t bitIndexR = 0b10000000 >> bitIndex;
	if ((Buffer[byteIndex] & bitIndexR) > 0) {
		return true;
	}
	return false;
};

void Bitmap::Set(uint64_t index, bool value) {
	uint64_t byteIndex = index / 8;
	uint8_t bitIndex = index % 8;
	uint8_t bitIndexR = 0b10000000 >> bitIndex;
	Buffer[byteIndex] &= ~bitIndexR;
	if (value) {
		Buffer[byteIndex] |= bitIndexR;
	}
}