#include "mouse.h"

uint8_t mousePointer[] = {
	0b10000000, 0b00000000,
	0b11000000, 0b00000000,
	0b10100000, 0b00000000,
	0b10010000, 0b00000000,
	0b10001000, 0b00000000,
	0b10000100, 0b00000000,
	0b10000010, 0b00000000,
	0b10000001, 0b00000000,
	0b10000011, 0b00000000,
	0b10000100, 0b00000000,
	0b10111100, 0b00000000,
	0b11000110, 0b00000000,
	0b00000110, 0b00000000,
	0b00000011, 0b00000000,
	0b00000010, 0b00000000,
	0b00000000, 0b00000000,
};

void mouseWait(){
    uint64_t timeout = 100000;
    while (timeout--){
        if ((inb(0x64) & 0b10) == 0){
            return;
        }
    }
}

void mouseWaitInput(){
    uint64_t timeout = 100000;
    while (timeout--){
        if (inb(0x64) & 0b1){
            return;
        }
    }
}

void mouseWrite(uint8_t value){
    mouseWait();
    outb(0x64, 0xD4);
    mouseWait();
    outb(0x60, value);
}

uint8_t mouseRead(){
    mouseWaitInput();
    return inb(0x60);
}

uint8_t mouseCycle = 0;
uint8_t mousePacket[4];
bool mousePacketReady = false;
Point mousePosition;
Point mousePositionOld;

void handlePS2Mouse(uint8_t data) {
	switch (mouseCycle)
	{
		case 0:
			if (mousePacketReady) break;
			if (data & 0b00001000 == 0) break;
			mousePacket[0] = data;
			mouseCycle++;
			break;

		case 1:
			if (mousePacketReady) break;
			mousePacket[1] = data;
			mouseCycle++;
			break;

		case 2:
			if (mousePacketReady) break;
			mousePacket[2] = data;
			mousePacketReady = true;
			mouseCycle = 0;
			break;
	}
}

void processMousePacket() {
	if (!mousePacketReady) return;

        bool xNegative, yNegative, xOverflow, yOverflow;

        if (mousePacket[0] & PS2XSign){
            xNegative = true;
        }else xNegative = false;

        if (mousePacket[0] & PS2YSign){
            yNegative = true;
        }else yNegative = false;

        if (mousePacket[0] & PS2XOverflow){
            xOverflow = true;
        }else xOverflow = false;

        if (mousePacket[0] & PS2YOverflow){
            yOverflow = true;
        }else yOverflow = false;

        if (!xNegative){
            mousePosition.X += mousePacket[1];
            if (xOverflow){
                mousePosition.X += 255;
            }
        } else
        {
            mousePacket[1] = 256 - mousePacket[1];
            mousePosition.X -= mousePacket[1];
            if (xOverflow){
                mousePosition.X -= 255;
            }
        }

        if (!yNegative){
            mousePosition.Y -= mousePacket[2];
            if (yOverflow){
                mousePosition.Y -= 255;
            }
        } else
        {
            mousePacket[2] = 256 - mousePacket[2];
            mousePosition.Y += mousePacket[2];
            if (yOverflow){
                mousePosition.Y += 255;
            }
        }

        if (mousePosition.X < 0) mousePosition.X = 0;
        if (mousePosition.X > GlobalRenderer->TargetFramebuffer->Width-1) mousePosition.X = GlobalRenderer->TargetFramebuffer->Width-1;
        
        if (mousePosition.Y < 0) mousePosition.Y = 0;
        if (mousePosition.Y > GlobalRenderer->TargetFramebuffer->Height-1) mousePosition.Y = GlobalRenderer->TargetFramebuffer->Height-1;
        
        GlobalRenderer->ClearMouseCursor(mousePointer, mousePositionOld);
        GlobalRenderer->DrawOverlayMouseCursor(mousePointer, mousePosition, 0xffffffff);

        if (mousePacket[0] & PS2Leftbutton) {
            // Left Button clicked
            // GlobalRenderer->PutChar('_', mousePosition.X, mousePosition.Y);
        }

        if (mousePacket[0] & PS2Middlebutton) {
            // Middle Button clicked
        }

        if (mousePacket[0] & PS2Rightbutton) {
            // Right Button clicked
            // uint32_t colour = GlobalRenderer->Colour;
            // GlobalRenderer->Colour = 0x0000ff00;
            // GlobalRenderer->PutChar('_', mousePosition.X, mousePosition.Y);
            // GlobalRenderer->Colour = colour;
        }

        mousePacketReady = false;
        mousePositionOld = mousePosition;
}

void initPS2Mouse() {
	outb(0x64, 0xA8); // Enable auxiliary device -> mouse
	mouseWait();

	outb(0x64, 0x20); // Tells keyboard controller we want to send a command to the mouse
	mouseWaitInput();

	uint8_t status = inb(0x60);
	status |= 0b10;
	mouseWait();
	outb(0x64, 0x60);
	mouseWait();
	outb(0x64, status); // Set correct bit in "compaq" status byte

	mouseWrite(0xF6);
	mouseRead();

	mouseWrite(0xF4);
	mouseRead();
}