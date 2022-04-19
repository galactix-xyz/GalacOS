#include "kernelUtil.h"
#include "userinput/mouse.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalRenderer->Print("Kernel Initialized Successfully");
    
        // ! ACPI Check script
        GlobalRenderer->Next();
        GlobalRenderer->Print(to_hstring((uint64_t)bootInfo->rsdp));
    /*
        GlobalRenderer->Next();

        GlobalRenderer->PutChar(*(uint8_t*)bootInfo->rsdp);
        
        // Check if RSDP has been located.
        for (int i = 1; i <= 7; i++) {
            GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + i));
        }
    */

    // Main loop of kernel
    while (true) {
        processMousePacket();
    }

    while(true);
}