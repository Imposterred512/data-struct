#include <stdio.h>
#include "list.h"
#include <stdlib.h>

void printModif(void* obj) {
    printf("%d ", *(int*)obj);
}

int main() {
    List* list = lcreate(sizeof(int), L_MV);
    for(int i = 0; i < 23; i++) {
        ladd(list, &i);
    }
    lprintAll(list, printModif);
    printf("\n");
    lremove(list, 3);
    lremoveAll(list);
    lprintAll(list, printModif);
    printf("\n");
    lfree(list);
    return 0;
}