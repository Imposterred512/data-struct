#ifndef MAP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define MAP_H

typedef struct {
    void* key;
    void* value;
} Entry;

typedef struct {
    int (*hash_func)(void*);
    int size;
    int key_size;
    int value_size;
    void** buckets;
} HashMap;

Bool hm_check(void* obj);
HashMap* hm_create(int (*func)(void*), int key_size, int value_size);
void hm_put(HashMap* map, void* key, void* value);
void* hm_get(HashMap* map, void* key);

#endif 