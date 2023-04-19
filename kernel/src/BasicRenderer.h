#pragma once
#include "math.h"
#include "Framebuffer.h"
#include "simpleFonts.h"
#include <stdint.h>

class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    uint32_t mouseCursorBuffer[16 * 16];
    uint32_t mouseCursorBufferAfter[16 * 16];
    unsigned int Colour;
    unsigned int ClearColour;
    void putPixel(uint32_t x, uint32_t y, uint32_t colour);
    uint32_t getPixel(uint32_t x, uint32_t y);
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    
    void Clear();
    void ClearChar();
    void Next();
    void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t colour);
    void ClearMouseCursor(uint8_t* mouseCursor, Point position);

    bool mouseDrawn;
};

extern BasicRenderer* GlobalRenderer;