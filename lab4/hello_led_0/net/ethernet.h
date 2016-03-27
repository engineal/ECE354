#ifndef ETHERNET_H
#define ETHERNET_H

void ethernetInit(char[]);

int ethernetSend(char*, int, char*, char*);
int ethernetSendNoACK(char*, int, char*, char*);
int ethernetReceive(char*, char*);

#endif /*ETHERNET_H*/
