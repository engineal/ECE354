#ifndef ETHERNET_H
#define ETHERNET_H

#include "layers/ethernet_layer.h"

#define ETHERNET_LENGTH         1546
#define ETHERNET_DATA_LENGTH    (ETHERNET_LENGTH-ETHERNET_HEADER_LENGTH)
//#define ETHERNET_MAX_DATA_LENGTH 1500

void ethernetInit(char[]);
void ethernet_worker();
void ethernetSend(char*, int, char*, char*);
void ethernetSendNoACK(char*, int, char*, char*);
int ethernetReceive(char*, char*);

#endif /*ETHERNET_H*/
