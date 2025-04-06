#include <stdio.h>
#include "seqlist.h"


int main(int argc, char const *argv[]) {
    SeqList* seqlist = seqlist_create(5);

    seqlist_insert(seqlist, 1, 2);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 1, 1);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 3, 3);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 4, 4);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 5, 5);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 4, 5);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 4, 7);
    seqlist_insert(seqlist, 4, 7);
    seqlist_display(seqlist);

    SeqListEleType delete_buf;
    size_t pos = 0;
    seqlist_remove(seqlist, 5, &delete_buf);
    seqlist_display(seqlist);

    seqlist_remove(seqlist, 1, &delete_buf);
    seqlist_display(seqlist);

    SeqListEleType search_buf = 3;
    size_t search_pos = 1;

    if (0) {
        seqlist_search(seqlist, &search_pos, &search_buf, 0);
        printf("search_pos: %zu    search_buf: %d\n", search_pos, search_buf);  
    } else {
        seqlist_search(seqlist, &search_pos, &search_buf, -1);
        printf("search_pos: %zu    search_buf: %d\n", search_pos, search_buf);
    }

    seqlist_clean(&seqlist);
    return 0;
}
