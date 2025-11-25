#include <stdio.h>
#include <stdlib.h>


typedef int MemoryPage;

typedef struct LRUCacheSingleStack {
    MemoryPage* pages;
    int length;
    int size;
} LRUCacheSingleStack;


LRUCacheSingleStack* LRUCacheSingleStack_create(int size) {
    if (size <= 0) {
        return NULL;
    }

    LRUCacheSingleStack* lru = (LRUCacheSingleStack*) malloc (
        sizeof(LRUCacheSingleStack) * size
    );

    if (lru == NULL) {
        return NULL;
    }

    lru->pages = (MemoryPage*) malloc (sizeof(MemoryPage) * size);

    if (lru->pages == NULL) {
        free(lru);
        return NULL;
    }

    lru->size = size;
    lru->length = 0;

    return lru;
}


int LRUCacheSingleStack_is_full(LRUCacheSingleStack* lru) {
    return lru->length >= lru->size;
}


int LRUCacheSingleStack_cache_is_exists(
    LRUCacheSingleStack* lru, MemoryPage page
) {
    for (int i = 0; i < lru->length; i++) {
        if (page == lru->pages[i]) {
            return 1;
        }
    }

    return 0;
}


void LRUCacheSingleStack_load(
    LRUCacheSingleStack* lru, MemoryPage page
) {
    if (LRUCacheSingleStack_is_full(lru)) {
        return;
    }

    lru->pages[lru->length++] = page;
}


MemoryPage LRUCacheSingleStack_drop(LRUCacheSingleStack* lru) {

    MemoryPage dropped = lru->pages[0];

    for (int i = 0; i < lru->length - 1; i++) {
        lru->pages[i] = lru->pages[i + 1];
    }

    lru->length--;

    return dropped;
}


void LRUCacheSingleStack_move_to_top(
    LRUCacheSingleStack* lru, MemoryPage page
) {
    
    int to_used = 0;
    MemoryPage to_used_cache;
    
    for (int i = 0; i < lru->length; i++) {
        if (page == lru->pages[i]) {
            to_used = i;
            to_used_cache = lru->pages[i];
            break;
        }
    }

    if (to_used != lru->length - 1) {
        for (int i = to_used; i < lru->length - 1; i++) {
            lru->pages[i] = lru->pages[i + 1];
        }

        lru->pages[lru->length - 1] = to_used_cache;
    }

}


void LRUCacheSingleStack_println(LRUCacheSingleStack* lru) {
    printf("LRU: {  ");
    for (int i = 0; i < lru->length; i++) {
        printf("%d  ", lru->pages[i]);
    }
    printf("}\n");
}


static void LRU_simulate_run() {
    MemoryPage pages[] = {
        7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2
    };

    int page_num = sizeof(pages) / sizeof(pages[0]);

    LRUCacheSingleStack* lru_cache = LRUCacheSingleStack_create(4);

    MemoryPage dorpped_cache[page_num];

    int dropped_cache_idx = 0;

    int drop_num = 0;

    for (int i = 0; i < page_num; i++) {
        if (LRUCacheSingleStack_cache_is_exists(lru_cache, pages[i])) {
            LRUCacheSingleStack_move_to_top(lru_cache, pages[i]);
        } else {
            if (LRUCacheSingleStack_is_full(lru_cache)) {
                dorpped_cache[dropped_cache_idx++] = LRUCacheSingleStack_drop(lru_cache);
            }
            LRUCacheSingleStack_load(lru_cache, pages[i]);
        }
    }

    for (int i = 0; i < dropped_cache_idx; i++) {
        printf("%d  ", dorpped_cache[i]);
    }
    putc('\n', stdout);
}


int main() {
    LRU_simulate_run();
}
