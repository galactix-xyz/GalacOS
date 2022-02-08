#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo){    
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    newRenderer.Print("Welcome to the kernel, you filthy animal!");

    while (true);
}