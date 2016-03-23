#ifndef HELLO_LED_H
#define HELLO_LED_H

int readSwitches();
void writeLEDs(int);
void ethernet_interrupts();
void writeDecimalLCD(int);

void interpretCommand(char* data, alt_u32 command);

void readFlash(char[][]);
void imageFlip(char[][]);
void imageInvert(char[][]);
void imageRotate(char[][]);

#endif /*HELLO_LED_H*/
