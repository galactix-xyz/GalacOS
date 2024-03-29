#pragma once
#include <stdint.h>
#include "acpi.h"
#include "paging/PageTableManager.h"
#include "BasicRenderer.h"
#include "cstr.h"

namespace PCI{
    struct PCIDeviceHeader{
        uint16_t VendorID;
        uint16_t DeviceID;
        uint16_t Command;
        uint16_t Status;
        uint8_t RevisionID;
        uint8_t ProgIF;
        uint8_t Subclass;
        uint8_t Class;
        uint8_t CacheLineSize;
        uint8_t LatencyTimer;
        uint8_t HeaderType;
        uint8_t BIST;
    };

    void EnumeratePCI(ACPI::MCFGHeader* mcfg);

	extern const char* DeviceClasses[];
	extern const char* GetVendorName(uint16_t VendorID);
	extern const char* GetDeviceName(uint16_t VendorID, uint16_t DeviceID);
	extern const char* SerialBusControllerSubclassName(uint8_t subclassCode);
	extern const char* BridgeDeviceSubclassName(uint8_t subclassCode);
	extern const char* GetSubclassName(uint8_t classCode, uint8_t subclassCode);
	extern const char* GetProgIFName(uint8_t classCode, uint8_t subclassCode, uint8_t progIF);
}