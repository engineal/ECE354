#ifndef ETHERNET_H
#define ETHERNET_H

void ethernetInit(char[]);

void ethernetSend(char*, int, char*, char*);
void ethernetSendNoACK(char*, int, char*, char*);
int ethernetReceive(char*, char*);

#endif /*ETHERNET_H*/
