#pragma once
#include "../efiMemory.h"
#include <stdint.h>
#include "../bitmap.h"
#include "../memory.h"

class PageFrameAlloc {
	public:
	void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
	Bitmap PageBitmap;
	void FreePage(void* addr);
	void LockPage(void* addr);
	void FreePages(void* addr, uint64_t pageCount);
	void LockPages(void* addr, uint64_t pageCount);
	void* RequestPage();
	uint64_t GetFreeRam();
	uint64_t GetUsedRam();
	uint64_t GetReservedRam();

	private:
	void InitBitmap(size_t bitmapSize, void* bufferAddr);
	void ReservePage(void* addr);
	void UnReservePage(void* addr);
	void ReservePages(void* addr, uint64_t pageCount);
	void UnReservePages(void* addr, uint64_t pageCount);
};

extern PageFrameAlloc GlobalAllocator;