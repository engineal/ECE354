#ifndef HELLO_LED_H
#define HELLO_LED_H

//#define MASTER

#ifdef MASTER

#define LOCAL_MAC {0x5D, 0x82, 0xD2, 0xEA, 0x03, 0x69}
#define LOCAL_IP_ADDR {192, 168, 1, 116}
#define LOCAL_PORT 20451

#define DEST_MAC {0x0D, 0xAE, 0xDC, 0xE2, 0xC6, 0x75}
#define DEST_IP_ADDR {192, 168, 1, 112}
#define DEST_PORT 1115

#else

#define LOCAL_MAC {0x0D, 0xAE, 0xDC, 0xE2, 0xC6, 0x75}
#define LOCAL_IP_ADDR {192, 168, 1, 112}
#define LOCAL_PORT 1115

#define DEST_MAC {0x5D, 0x82, 0xD2, 0xEA, 0x03, 0x69}
#define DEST_IP_ADDR {192, 168, 1, 116}
#define DEST_PORT 20451

#endif

#endif /*HELLO_LED_H*/
