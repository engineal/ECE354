#include "helper.h"

void charncpy(unsigned char* dest, const char *src, int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void charncat(unsigned char* dest, const char *src, int* s, int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i + *s] = src[i];
    }
    *s += n;
}

void charnuncat(unsigned char* dest, const char *src, int* s, int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i] = src[i + *s];
    }
    *s += n;
}
