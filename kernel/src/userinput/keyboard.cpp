#include "keyboard.h"

bool LeftShiftPressed;
bool RightShiftPressed;

void HandleKeyboard(uint8_t scancode) {
	
	switch (scancode)
	{
		case LeftShift:
			LeftShiftPressed = true;
			return;

		case LeftShift + 0x80:
			LeftShiftPressed = false;
			return;

		case RightShift:
			RightShiftPressed = true;
			return;

		case RightShift + 0x80:
			RightShiftPressed = false;
			return;

		case Enter:
			GlobalRenderer->Next();
			return;

		case Spacebar:
			GlobalRenderer->PutChar(' ');
			return;

		case BackSpace:
			GlobalRenderer->ClearChar();
			break;
	}
	
	char ascii = QWERTY_US_Keyboard::translate(scancode, LeftShiftPressed | RightShiftPressed);

	if (ascii != 0) {
		GlobalRenderer->PutChar(ascii);
	}
}