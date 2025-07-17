#include <stdio.h>
#include "seqlist.h"


int main(int argc, char const *argv[]) {
    SeqList* seqlist = SeqList_create(5, SEQLIST_INIT_DISABLE, NULL);

    SeqList_insert(seqlist, 1, 2);
    SeqList_display(seqlist);

    SeqList_insert(seqlist, 1, 1);
    SeqList_display(seqlist);

    SeqList_insert(seqlist, 3, 3);
    SeqList_display(seqlist);

    SeqList_insert(seqlist, 4, 4);
    SeqList_display(seqlist);

    SeqList_insert(seqlist, 5, 5);
    SeqList_display(seqlist);

    SeqList_insert(seqlist, 4, 5);
    SeqList_display(seqlist);

    SeqList_insert(seqlist, 4, 7);
    SeqList_insert(seqlist, 4, 7);
    SeqList_display(seqlist);

    SeqListEleType delete_buf;
    size_t pos = 0;
    SeqList_remove(seqlist, 5, &delete_buf);
    SeqList_display(seqlist);

    SeqList_remove(seqlist, 1, &delete_buf);
    SeqList_display(seqlist);

    SeqListEleType search_buf = 3;
    size_t search_pos = 1;

    if (0) {
        SeqList_search(seqlist, &search_pos, &search_buf, 0);
        printf("search_pos: %zu    search_buf: %d\n", search_pos, search_buf);  
    } else {
        SeqList_search(seqlist, &search_pos, &search_buf, -1);
        printf("search_pos: %zu    search_buf: %d\n", search_pos, search_buf);
    }

    SeqList_clean(&seqlist);
    return 0;
}
