#include "helper.h"

// copies n bytes from src to dest.
void charncpy(unsigned char* dest, const char *src, int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        dest[i] = src[i];
    }
}

// appends n bytes from src to end of dest.
void charncat(unsigned char* dest, const char *src, int* s, int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        dest[i + *s] = src[i];
    }
    *s += n;
}

// starting at location s, assigns n bytes from src into dest.
// updates value of s to point to the next unused byte in src. 
void charnuncat(unsigned char* dest, const char *src, int* s, int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        dest[i] = src[i + *s];
    }
    *s += n;
}
