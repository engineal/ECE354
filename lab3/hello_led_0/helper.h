#ifndef HELPER_H
#define HELPER_H

void charncpy(char*, const char*, int);
void charncat(char*, const char*, int*, int);
void charnuncat(char*, const char*, int*, int);

int computeChecksum(char*, int);

void int_to_char(char*, int, int*, int);
int char_to_int(const char*, int*, int);

#endif /*HELPER_H*/
