#ifndef UDP_H
#define UDP_H

#include "layers/udp_layer.h"
#include "ip.h"

#define UDP_LENGTH       IP_DATA_LENGTH
#define UDP_DATA_LENGTH  (UDP_LENGTH-UDP_HEADER_LENGTH)

void udpSend(char*, int, int, int, char*, char*, char*);
int udpReceive(char*, int, char*);

#endif /*UDP_H*/
