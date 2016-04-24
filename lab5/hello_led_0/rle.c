#include "rle.h"
#include "basic_io.h"
#include "image.h"

int hwCompressImage(char* output, char image[][Y]) {
    int n = 0; 
    int outputLength = 0;
    char bitImage[X*Y/8];
    
    charToBit(image, bitImage);
   
    outport(RLE_FLUSH_PIO_BASE, 0);
    while(n<(X*Y/8))
    {
        if(!inport(FIFO_IN_FULL_PIO_BASE))
        {
            outport(FIFO_IN_WRITE_REQ_PIO_BASE, 1);
            outport(ODATA_PIO_BASE, bitImage[n]);
            //output(FIFO_IN_WRITE_REQ_PIO_BASE, 1);
            //output(FIFO_IN_WRITE_REQ_PIO_BASE, 0); ?
        }
        
        if(inport(RESULT_READY_PIO_BASE))
        {
            outport(FIFO_OUT_READ_REQ_PIO_BASE, 1);
            int rleData = inport(IDATA_PIO_BASE);
            output[outputLength++] = (rleData >> 16) & 0xFF;
            output[outputLength++] = (rleData >> 8)  & 0xFF;
            output[outputLength++] = (rleData)       & 0xFF;
            
            outport(FIFO_OUT_READ_REQ_PIO_BASE, 0);
            
            if(n<10)
            {
                printf("%x", rleData);
            }
        }
        
    }
    outport(RLE_FLUSH_PIO_BASE, 1);
    //output(RLE_FLUSH_PIO_BASE, 0);
    return outputLength;
}

int compressImage(char* output, char image[][Y]) {
    int x, y;
    int outputLength = 0;
    unsigned int num = 0;
    unsigned char bit = image[0][0] & 0x01;
    
    for (x = 0; x < X; x++) {
        for (y = 0; y < Y; y++) {
            if (bit == (image[x][y] & 0x01)) {
                num++;
            } else {
                output[outputLength++] = (bit << 7) | ((num >> 16) & 0x7F);
                output[outputLength++] = (num >> 8) & 0xFF;
                output[outputLength++] = num & 0xFF;
                
                num = 1;
                bit = image[x][y] & 0x01;
            }
        }
    }
    
    // make sure end bytes are written
    output[outputLength++] = (bit << 7) | ((num >> 16) & 0x7F);
    output[outputLength++] = (num >> 8) & 0xFF;
    output[outputLength++] = num & 0xFF;
    
    return outputLength;
}

void decompressImage(char output[][Y], char* input, int inputLength) {
    int i, j;
    int x = 0;
    int y = 0;
    for (i = 0; i < inputLength; i += 3) {
        unsigned int num = ((input[i] & 0x7F) << 16) | ((input[i + 1] & 0xFF) << 8) | (input[i + 2] & 0xFF);
        unsigned char bit = (input[i] >> 7) & 0x01;
        
        for (j = 0; j < num; j++) {
            output[x][y] = bit;
            y++;
            if (y == 480) {
                y = 0;
                x++;
            }
        }
    }
}
