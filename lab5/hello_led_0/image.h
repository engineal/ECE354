#ifndef IMAGE_H
#define IMAGE_H

#define X 640
#define Y 480

void readFlash(char[][]);
int charToBit(char[][], char[]);
void bitToChar(char[], char[][]);
void imageFlip(char[][]);
void imageInvert(char[][]);
void imageRotate(char[][]);
int compareArrays(char[][], char[][]);

#endif /*IMAGE_H*/
