#include "map.h"

Bool hm_check(void* obj) {
    if(obj != NULL)
        return TRUE;
    return FALSE;
}

HashMap* hm_create(int (*func)(void*), int key_size, int value_size) {
    int capacity = 256;
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->hash_func = func;
    map->size = capacity;
    map->key_size = key_size;
    map->value_size = value_size;
    map->buckets = (void**)calloc(capacity, sizeof(void*));
    return map;
}

void hm_put(HashMap* map, void* key, void* value) {
    if( hm_check(map) == FALSE || hm_check(key) == FALSE || hm_check(value) == FALSE) {
        printf("%s\n", "Error hm_put: One of the arguments is NULL");
    }
    int index = map->hash_func(key) % map->size;
    if(map->buckets[index] == NULL) {
        map->buckets[index] = lcreate(sizeof(Entry), L_MV);
    }
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = malloc(map->key_size);
    entry->value = malloc(map->value_size);
    memmove(entry->key, key, map->key_size);
    memmove(entry->value, value, map->value_size);
    ladd((List*)map->buckets[index], entry);
    free(entry);
}

void* hm_get(HashMap* map, void* key) {
    if( hm_check(map) == FALSE || hm_check(key) == FALSE) {
        printf("%s\n", "Error hm_get: One of the arguments is NULL");
        return NULL;
    }
    int index = map->hash_func(key) % map->size;
    if (map->buckets[index] == NULL || ((List*)(map->buckets[index]))->array == NULL) {
        printf("Error hm_get: Bucket or its array is NULL\n");
        return NULL;
    }
    for(int i = 0; i < ((List*)(map->buckets[index]))->size; i++) {
        Entry* entry = (Entry*)((List*)(map->buckets[index]))->array[i];
        if(memcmp(entry->key, key, map->key_size) == 0){
            return entry->value;
        }
    }
    return NULL;
}