#ifndef INTERPRETCOMMAND_H
#define INTERPRETCOMMAND_H

#define MSG_ACK            0xAA
#define MSG_NAK            0xFF
#define MSG_GET_IMAGE      0x00
#define MSG_TRANSMIT_IMAGE 0x01
#define MSG_IMAGE_PROC_1   0x02
#define MSG_IMAGE_PROC_2   0x03
#define MSG_IMAGE_PROC_3   0x04
#define MSG_IMAGE_PROC_4   0x05
#define MSG_IMAGE_PROC_5   0x06
#define MSG_IMAGE_PROC_6   0x07

#define MAX_PAYLOAD_LENGTH 1471 //1500 for max ethernet length, -28 for IP,UDP headers. -1 for off by one error

void interpretCommand(int command);

#endif /*INTERPRETCOMMAND_H*/