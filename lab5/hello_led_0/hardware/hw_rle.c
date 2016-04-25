#include "hw_rle.h"
#include "basic_io.h"

void fifo_in_write_byte(char byte) {
    outport(ODATA_PIO_BASE, byte);
    outport(FIFO_IN_WRITE_REQ_PIO_BASE, 1);
    outport(FIFO_IN_WRITE_REQ_PIO_BASE, 0);    
}

int fifo_in_full() {
    return inport(FIFO_IN_FULL_PIO_BASE);
}

void rle_flush() {
    outport(RLE_FLUSH_PIO_BASE, 1);
    outport(RLE_FLUSH_PIO_BASE, 0);
}

int fifo_out_read_byte() {
    outport(FIFO_OUT_READ_REQ_PIO_BASE, 1);
    int result = inport(IDATA_PIO_BASE);
    outport(FIFO_OUT_READ_REQ_PIO_BASE, 0);
    return result;
}

int fifo_out_ready() {
    return !inport(RESULT_READY_PIO_BASE);
}
