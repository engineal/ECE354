#include "helper.h"

// copies n bytes from src to dest.
void charncpy(char* dest, const char *src, int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        dest[i] = src[i];
    }
}

// appends n bytes from src to end of dest.
void charncat(char* dest, const char *src, int* s, int n) 
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
void charnuncat(char* dest, const char *src, int s, int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        dest[i] = src[i + s];
    }
}

// copies n bytes from src to the dest char array starting at s
void int_to_char(char* dest, unsigned int src, int* s, int n) {
    int i;
    for (i = 0; i < n; i++)
    {
        dest[i + *s] = src >> (8*(n-1-i));
    }
    *s += n;
}

// Computes checksum on a set of data, assuming data 
// is in 16bits.  Returns the computed checksum.
int computeChecksum(char* data, int len)
{
    int i;
    unsigned int sum = 0;

    // Increment by 2 as we are working in 16bits.
    for (i = 0; i < len; i+=2)
    {
        if (i + 1 < len)
            sum += (data[i] << 8) | data[i+1];
        else
            sum += (data[i] << 8) | 0x00;
        if (sum > 0xFFFF)
            sum = (sum & 0xFFFF) + 1;
    }

    // Compute 1's complement on the sum.
    return (~sum) & 0xFFFF; 
}

int max(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int min(int x, int y) {
    if (x < y)
        return x;
    else
        return y;
}