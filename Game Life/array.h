#ifndef ARRAY_H
#define ARRAY_H

char** createArray(const int& rows, const int& columns);
void deleteArray(char** arr, const int& rows);
void printArray(char** arr, const int& rows, const int& columns);

#endif