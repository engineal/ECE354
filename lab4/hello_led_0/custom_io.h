#ifndef CUSTOM_IO_H
#define CUSTOM_IO_H

int readSwitches();
int readButtons();
void writeLEDs(int);
void writeGreenLEDs(int);
void writeDecimalLCD(int);

void init_vga();
void write_vga(char[][]);

#endif /*CUSTOM_IO_H*/
