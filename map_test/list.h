#ifndef LIST_H
#define LIST_H

typedef enum {
    L_CP, L_MV, L_SK
} Mode;

typedef enum {
    TRUE, FALSE
} Bool;

typedef struct {
    int size;
    int capacity;
    int item_size;
    Mode mode;
    void** array;
} List;

Bool lcheck(void* arg);
List* lcreate(int item_size, Mode mode);
void ladd(List* list, void* elem);
void lprintAll(List* list,  void (*func)(void*));
void lremove(List* list, int index);
void lremoveAll(List* list);
void* lget(List* list, int index);
void lfree(List* list);
#endif