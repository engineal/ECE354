#ifndef HW_RLE_H
#define HW_RLE_H

void fifo_in_write_byte(char);
int fifo_in_full();
void rle_flush();
int fifo_out_read_byte();
int fifo_out_ready();

#endif /*HW_RLE_H*/
