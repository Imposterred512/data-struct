#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Bool lcheck(void* arg) {
    if(arg != NULL)
        return TRUE;
    return FALSE;
}
List* lcreate(int item_size, Mode mode) {
    if(item_size <= 0){
        printf("Error: Incorrect item_size\n");
        return NULL;
    }
    int size = 10;
    List* list = (List*)malloc(sizeof(List));
    list->size = 0;
    list->capacity = size;
    list->item_size = item_size;
    list->mode = mode;
    list->array = (void**)calloc(size, sizeof(void*));

    if(mode == L_CP || mode == L_MV)
        for(int i = 0; i < size; i++)
            list->array[i] = (void*)malloc(item_size);

    return list;
}
void ladd(List* list, void* elem) {
    if(lcheck(list) == FALSE || lcheck(elem) == FALSE) {
        printf("Error ladd: One of the arguments is NULL\n");
        return;
    }
    if(list->size >= list->capacity) {
        list->capacity += list->capacity/3;
        list->array = (void**)realloc(list->array, list->capacity * sizeof(void*));
        if(list->mode == L_CP || list->mode == L_MV) {
            for(int i = list->size; i < list->capacity; i++)
                list->array[i] = (void*)malloc(list->item_size);
        }
    }
    switch(list->mode) {
        case L_CP:
            memmove(list->array[list->size], elem, list->item_size);
            break;
        case L_MV: 
            memmove(list->array[list->size], elem, list->item_size);
            elem = NULL;
            break;
        case L_SK:
            list->array[list->size] = elem;
            break;
    }
    list->size++;
}
void lprintAll(List* list,  void (*func)(void*)) {
    if(lcheck(list) == FALSE || lcheck(func) == FALSE) {
        printf("Error lprintAll: One of the arguments is NULL\n");
        return;
    }
    for(int i = 0; i < list->size; i++) 
        func(list->array[i]);
}
void lremove(List* list, int index) {
    if(lcheck(list) == FALSE) {
        printf("Error lremove: list is NULL\n");
        return;
    }
    if(0 >= index || index > list->capacity) {
        printf("Error lremove: Incorrect index\n");
        return;
    }
    if(list->mode == L_CP || list->mode == L_MV) {
        free(list->array[index]);
    }
    list->array[index] = NULL;
    memmove(&list->array[index], &list->array[index+1], (list->capacity-index-1) * sizeof(void*));
    if(list->mode == L_CP || list->mode == L_MV) {
        free(list->array[list->size-1]);
        list->array[list->size-1] = (void*)malloc(list->item_size);
    }else {
        list->array[list->size-1] = NULL; 
    }
    list->size--;
}
void lremoveAll(List* list){
    if(list->mode == L_CP || list->mode == L_MV) {
        for(int i = 0; i < list->size; i++) {
            free(list->array[i]);
        }
    }
    free(list->array);
    list->array = (void**)calloc(list->size, sizeof(void*));
    if(list->mode == L_CP || list->mode == L_MV) {
        for(int i = list->size; i < list->capacity; i++)
            list->array[i] = (void*)malloc(list->item_size);
    }
    list->size = 0;
}
void* lget(List* list, int index) {
    if(list == NULL) {
        printf("Error lget: Pointer to the list is NULL");
        return NULL;
    }
    if(0 > index || index > list->capacity){
        printf("Error lget: Incorrect index");
        return NULL;
    }
    return list->array[index];
}
void lfree(List* list) {
    if(list->mode == L_CP || list->mode == L_MV)
        for(int i = 0; i < list->capacity-1; i++)
            free(list->array[i]);
    free(list);
    list = NULL;
}