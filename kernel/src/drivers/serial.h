#pragma once
#include <stdint.h>
#include "../io.h"
#include "../panic.h"
#include "../BasicRenderer.h"

int InitSerial();
int serial_received();
char read_serial();
int is_transmit_empty();
void write_serial(char a);