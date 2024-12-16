#include "util.h"
#include <stdlib.h>
#include <string.h>

int listInit(List* l, int max_elmt_size) {
    l->data = malloc(max_elmt_size * 10); // Initial capacity of 10 elements
    if (l->data == NULL) {
        return -1; // Memory allocation failed
    }
    l->size = 0;
    l->capacity = 10;
    l->element_size = max_elmt_size;
    return 0;
}

void listAdd(List* l, void* element) {
    if (l->size == l->capacity) {
        l->capacity *= 2;
        l->data = realloc(l->data, l->capacity * l->element_size);
    }
    memcpy((char*)l->data + l->size * l->element_size, element, l->element_size);
    l->size++;
}

void listFree(List* l) {
    free(l->data);
    l->data = NULL;
    l->size = 0;
    l->capacity = 0;
    l->element_size = 0;
}

void *listGet(List* l, int index) {
    if (index < 0 || index >= l->size) {
        return NULL; // Index out of bounds
    }
    return (char*)l->data + index * l->element_size;
}