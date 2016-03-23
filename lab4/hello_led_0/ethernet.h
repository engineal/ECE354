#ifndef ETHERNET_H_
#define ETHERNET_H_

#include "basic_io.h"
#include "helper.h"
#include "ethernet_layer.h"
#include "IP_layer.h"
#include "UDP_layer.h"

void encode_message(
    char* data, int valueSize, 
    int port, int destPort, 
    char* destIP, char* ip_addr, 
    char* destMAC, char* ether_addr);
int decode_message(char* data, int dataLength, char* returnedData, int port, char* ip_addr, char* ether_addr);

#endif /*ETHERNET_H_*/
