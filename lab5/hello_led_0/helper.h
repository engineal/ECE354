#ifndef HELPER_H
#define HELPER_H

void charncpy(char*, const char*, int);
void charncat(char*, const char*, int*, int);
void charnuncat(char*, const char*, int, int);
void int_to_char(char*, unsigned int, int*, int);

int computeChecksum(char*, int);

int max(int, int);
int min(int, int);

#endif /*HELPER_H*/
