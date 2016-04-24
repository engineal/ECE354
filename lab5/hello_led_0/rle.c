#include "rle.h"
#include "basic_io.h"
#include "image.h"

int hw_compressImage(char* output, char image[][Y]) {
    return 0;
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
