#include "image.h"
#include "basic_io.h"
#include "sys/alt_flash.h"
#include "sys/alt_flash_types.h"

void readFlash(char image[][Y]) {
    alt_flash_fd* fd;
    unsigned int offset = 0x10;
    char bin_pix;
    fd = alt_flash_open_dev(CFI_FLASH_0_NAME);
    if (fd==NULL) 
    {
        printf("Flash memory open failure\n");
        return;
    }

    printf("Reading binary pixel from flash memory\n");
    int i, j;
    for(i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            alt_read_flash(fd,offset++,&bin_pix,1);
            image[i][j] = bin_pix;
        }
    }
    alt_flash_close_dev(CFI_FLASH_0_NAME);
}

int charToBit(char image[][Y], char output[]) {
    int i, j, a;
    int offset = 0;
    unsigned char temp;
    
    for (i = 0; i < X; i++) {
        j = 0;
        while (j < Y) {
            temp = 0;
            for (a = 0; a < 8; a++) {
                temp |= image[i][j + a] << (7 - a);
            }
            output[offset++] = temp;
            j += 8;
        }
    }
    
    return offset;
}

void imageFlip(char image[][Y]) {
    char cpy[X][Y];
    int i, j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            cpy[X - i][j] = image[i][j];
        }
    }
    
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            image[i][j] = cpy[i][j];
        }
    }
}

void imageInvert(char image[][Y]) {
    int i, j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            image[i][j] = !image[i][j];
        }
    }
}

void imageRotate(char image[][Y]) {
    char cpy[X][Y];
    int i, j;
    for(i = 0; i < X; i++) {
        for(j = 0; j < Y; j++) {
            if (i > 80 && i < 560) {
                cpy[i][j] = image[j][i];
            } else {
                cpy[i][j] = 0;
            }
        }
    }
    
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            image[i][j] = cpy[i][j];
        }
    }
}