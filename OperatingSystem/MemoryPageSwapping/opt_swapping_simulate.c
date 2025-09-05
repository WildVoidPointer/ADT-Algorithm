#include<stdio.h>


typedef struct {
    int* pages;
    int prev_drop_page;
    int page_num;
    int size;
    int swap_count;
} SimplePageList;


int SimplePageList_is_lack(SimplePageList* spl, int page) {

    for (int i = 0; i < spl->page_num; i++) {
        if (page == spl->pages[i]) {
            return 0;
        }
    }

    return 1;
}


void SimplePageList_println(SimplePageList* spl) {
    printf("SimplePageList: {  ");
    for (int i = 0; i < spl->page_num; i++) {
        printf("%d  ", spl->pages[i]);
    }
    printf(
        "prev_drop_page: %d  swap_count: %d  }\n", 
        spl->prev_drop_page,
        spl->swap_count
    );
}


void OPT_page_swap(
    SimplePageList* spl, int require_pages[], int req_pages_num, 
    int curr_req_page_idx
) {
    if (spl->page_num < spl->size) {
        spl->pages[spl->page_num++] = require_pages[curr_req_page_idx];
        return;
    }
    
    int drop_page_idx = -1;
    int prev_farthest_use = -1;
    
    // 为每个内存中的页面查找下一次使用的位置
    for (int i = 0; i < spl->page_num; i++) {
        int next_used_count = req_pages_num; // 默认永远不会再使用
        
        for (int j = curr_req_page_idx + 1; j < req_pages_num; j++) {
            if (spl->pages[i] == require_pages[j]) {
                next_used_count = j;
                break;
            }
        }
        
        // 如果这个页面永远不会再使用，立即选择它
        if (next_used_count == req_pages_num) {
            drop_page_idx = i;
            break;
        }
        
        // 选择最晚使用的页面
        if (next_used_count > prev_farthest_use) {
            prev_farthest_use = next_used_count;
            drop_page_idx = i;
        }
    }

    spl->prev_drop_page = spl->pages[drop_page_idx];
    spl->pages[drop_page_idx] = require_pages[curr_req_page_idx];
    spl->swap_count++;
}


void optimal_replacement_algorithm_simulate(
    SimplePageList* spl, int pages[], int page_num
) {
    for (int i = 0; i < page_num; i++) {
        if (SimplePageList_is_lack(spl, pages[i])) {
            OPT_page_swap(spl, pages, page_num, i);
        }
        SimplePageList_println(spl);
    }
}


int main() {
    int spl_pages[3];

    SimplePageList spl = {
        .pages = spl_pages, .page_num = 0,
        .size = 3, .prev_drop_page = -1,
        .swap_count = 0
    };

    int pages[] = {
        7, 0, 1, 2, 0, 3, 0, 4,
        2, 3, 0, 3, 2, 1, 2, 0, 
        1, 7, 0, 1
    };

    int page_num = sizeof(pages) / sizeof(pages[0]);

    optimal_replacement_algorithm_simulate(&spl, pages, page_num);

    return 0;
}
