#ifndef HELLO_LED_H_
#define HELLO_LED_H_

int readSwitches();
void writeLEDs(int);
void encode_message(int);
void decode_message();
void ethernet_interrupts();

#endif /*HELLO_LED_H_*/
