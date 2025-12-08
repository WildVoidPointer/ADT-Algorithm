#include <stdio.h>
#include <stdlib.h>


typedef int MemoryPage;

typedef struct LRUCacheDoubleStack {
    MemoryPage* main_cache;
    MemoryPage* help_cache;
    int main_length;
    int help_length;
    int cache_num;
    int cache_size;
} LRUCacheDoubleStack;


LRUCacheDoubleStack* LRUCacheDoubleStack_create(int size) {
    if (size <= 0) {
        return NULL;
    }

    LRUCacheDoubleStack* lru = (LRUCacheDoubleStack*) malloc (
        sizeof(LRUCacheDoubleStack)
    );

    if (lru == NULL) {
        return NULL;
    }

    // 分配主栈
    lru->main_cache = (MemoryPage*) malloc (sizeof(MemoryPage) * size);
    if (lru->main_cache == NULL) {
        free(lru);
        return NULL;
    }

    // 分配辅助栈
    lru->help_cache = (MemoryPage*) malloc (sizeof(MemoryPage) * size);
    if (lru->help_cache ==  NULL) {
        free(lru->main_cache);
        free(lru);
        return NULL;
    }

    lru->cache_size = size;
    lru->cache_num = 0;
    lru->main_length = lru->help_length = 0;

    return lru;
}


int _LRUCacheDoubleStack_stack_is_empty(int st_len) {
    return st_len <= 0;
}


void _LRUCacheDoubleStack_push(
    MemoryPage* st, int* st_len, MemoryPage page
){
    st[(*st_len)++] = page;
}


MemoryPage _LRUCacheDoubleStack_pop(MemoryPage* st, int* st_len) {
    return st[--(*st_len)];
}


int _LRUCacheDoubleStack_peek_verify(
    MemoryPage* st, int st_len, MemoryPage page
) {
    return st[st_len - 1] == page;
}


int LRUCacheDoubleStack_is_full(LRUCacheDoubleStack* lru){
    return lru->cache_num >= lru->cache_size;
}


int LRUCacheDoubleStack_is_empty(LRUCacheDoubleStack* lru){
    return lru->cache_num <= 0;
}


void LRUCacheDoubleStack_load(
    LRUCacheDoubleStack* lru, MemoryPage page
) {
    _LRUCacheDoubleStack_push(
        lru->main_cache, 
        &(lru->main_length), 
        page
    );
    
    lru->cache_num++;
}


MemoryPage LRUCacheDoubleStack_drop(LRUCacheDoubleStack* lru) {
    if (_LRUCacheDoubleStack_stack_is_empty(lru->help_length)) {
        while (!  _LRUCacheDoubleStack_stack_is_empty(lru->main_length)) {
            _LRUCacheDoubleStack_push(
                lru->help_cache, 
                &(lru->help_length), 
                _LRUCacheDoubleStack_pop(
                    lru->main_cache, 
                    &(lru->main_length)
                )
            );
        }
    }

    MemoryPage dropped = _LRUCacheDoubleStack_pop(
        lru->help_cache, &(lru->help_length)
    );

    lru->cache_num--;
    return dropped;
}


int LRUCacheDoubleStack_cache_is_exists(
    LRUCacheDoubleStack* lru, MemoryPage page
) {
    
    int is_exists = 0;
    
    if (!  LRUCacheDoubleStack_is_empty(lru)) {

        for (int i = 0; i < lru->main_length; i++) {
            if (lru->main_cache[i] == page) {
                is_exists = 1;
                break;
            }
        }

        for (int i = 0; i < lru->help_length; i++) {
            if (lru->help_cache[i] == page) {
                is_exists = 1;
                break;
            }
        }
    }

    return is_exists;
}


void LRUCacheDoubleStack_move_to_top(
    LRUCacheDoubleStack* lru, MemoryPage page
) {
    if (!  LRUCacheDoubleStack_is_empty(lru)) {
        int old_length = lru->help_length;
        int is_find = 0;
        MemoryPage access_page;

        // 扫描主栈
        while (
            !  _LRUCacheDoubleStack_stack_is_empty(lru->main_length) 
            && !  is_find
        ) {

            if (!  _LRUCacheDoubleStack_peek_verify(
                    lru->main_cache, lru->main_length, page
                )
            ) {
                _LRUCacheDoubleStack_push(
                    lru->help_cache, 
                    &(lru->help_length),
                    _LRUCacheDoubleStack_pop(
                        lru->main_cache, 
                        &(lru->main_length)
                    )
                );
            } else {
                access_page = _LRUCacheDoubleStack_pop(
                    lru->main_cache, &(lru->main_length)
                );
                is_find = 1;
            }
        }

        // 复原辅助栈
        while (lru->help_length != old_length) {
            _LRUCacheDoubleStack_push(
                lru->main_cache, 
                &(lru->main_length),
                _LRUCacheDoubleStack_pop(
                    lru->help_cache, 
                    &(lru->help_length)
                )
            ); 
        }

        // 扫描辅助栈
        old_length = lru->main_length;

        while (
            !  _LRUCacheDoubleStack_stack_is_empty(lru->help_length)
            && !  is_find
        ) {

            if (!  _LRUCacheDoubleStack_peek_verify(
                    lru->help_cache, lru->help_length, page
                )
            ) {
                _LRUCacheDoubleStack_push(
                    lru->main_cache, 
                    &(lru->main_length),
                    _LRUCacheDoubleStack_pop(
                        lru->help_cache, 
                        &(lru->help_length)
                    )
                );
            } else {
                access_page = _LRUCacheDoubleStack_pop(
                    lru->help_cache, 
                    &(lru->help_length)
                );
                is_find = 1;
            }
        }

        // 复原主栈
        while (lru->main_length != old_length) {
            _LRUCacheDoubleStack_push(
                lru->help_cache, 
                &(lru->help_length),
                _LRUCacheDoubleStack_pop(lru->main_cache, &(lru->main_length))
            ); 
        }

        // 将访问页置顶
        _LRUCacheDoubleStack_push(
            lru->main_cache, 
            &(lru->main_length), 
            access_page
        );
    }
}


static void LRU_simulate_run() {
    MemoryPage pages[] = {
        7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2
    };

    int page_num = sizeof(pages) / sizeof(pages[0]);

    LRUCacheDoubleStack* lru_cache = LRUCacheDoubleStack_create(4);

    MemoryPage dorpped_cache[page_num];

    int dropped_cache_idx = 0;

    int drop_num = 0;

    for (int i = 0; i < page_num; i++) {
        if (LRUCacheDoubleStack_cache_is_exists(lru_cache, pages[i])) {
            LRUCacheDoubleStack_move_to_top(lru_cache, pages[i]);

        } else {

            if (LRUCacheDoubleStack_is_full(lru_cache)) {
                dorpped_cache[dropped_cache_idx++] = LRUCacheDoubleStack_drop(lru_cache);
            }
            LRUCacheDoubleStack_load(lru_cache, pages[i]);
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
