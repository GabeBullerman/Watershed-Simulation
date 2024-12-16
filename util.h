#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

// Macro to calculate the index in a 1D array for an element in a 2D array
#define INDEX(row, column, num_columns) ((row) * (num_columns) + (column))

// Prototype for the allocateArray function
void *allocateArray(int rows, int columns);

// List structure definition
typedef struct {
    void *data;
    int size;
    int capacity;
    int element_size;
} List;

// Function prototypes for List operations
int listInit(List* l, int max_elmt_size);
void listAdd(List* l, void* elmt);
void listFree(List* l);
void *listGet(List* l, int index);

#endif // UTIL_H