#include <stdio.h>
#include "map.h"
#define DEREFERENCIN(ptr, type1) (*(type1*)(ptr));

int hashCode(void* obj) {
    return *(int*)obj;
}

int main() {
    HashMap* hmap = hm_create(hashCode, sizeof(int), sizeof(int));
    
    for(int i = 0; i < 43; i++) {
        int* key = (int*)malloc(sizeof(int));  
        *key = i; 
        int* value = (int*)malloc(sizeof(int));
        *value = i * 10;
        hm_put(hmap, key, value); 
    }

    if (hmap) {
        printf("HashMap created successfully!\n");
        for(int i = 0; i < 43; i++) {
            int* result = (int*)hm_get(hmap, (void*)&i);
            printf("%d ", *result);
        }
        for (int j = 0; j < 43; j++) {
            free(hmap->buckets[j]);
        }
        free(hmap->buckets);
        free(hmap);
    }
    return 0;
}
