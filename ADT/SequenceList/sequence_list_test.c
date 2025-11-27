#include "sequence_list.h"


#include <stdio.h>


int main(int argc, char const *argv[]) {
    
    SequenceList* seqlist = SequenceList_create(5);

    SequenceList_insert(seqlist, 1, 2);
    SequenceList_display(seqlist);

    SequenceList_insert(seqlist, 1, 1);
    SequenceList_display(seqlist);

    SequenceList_insert(seqlist, 3, 3);
    SequenceList_display(seqlist);

    SequenceList_insert(seqlist, 4, 4);
    SequenceList_display(seqlist);

    SequenceList_insert(seqlist, 5, 5);
    SequenceList_display(seqlist);

    SequenceList_insert(seqlist, 4, 5);
    SequenceList_display(seqlist);

    SequenceList_expand(seqlist, 1);
    SequenceList_display(seqlist);

    SequenceList_insert(seqlist, 4, 7);
    SequenceList_display(seqlist);
    
    SequenceList_insert(seqlist, 4, 7);
    SequenceList_display(seqlist);

    SequenceListDataType delete_buf;
    size_t pos = 0;
    SequenceList_remove(seqlist, 5, &delete_buf);
    SequenceList_display(seqlist);

    SequenceList_remove(seqlist, 1, &delete_buf);
    SequenceList_display(seqlist);

    SequenceListDataType search_buf = 3;
    size_t search_pos = 1;

    if (0) {
        SequenceList_search(seqlist, &search_pos, &search_buf, 0);
        printf(
            "search_pos: %zu    search_buf: %d\n", 
            search_pos, 
            search_buf
        );  

    } else {
        SequenceList_search(seqlist, &search_pos, &search_buf, -1);
        printf(
            "search_pos: %zu    search_buf: %d\n", 
            search_pos, 
            search_buf
        );
    }

    SequenceList_destroy(&seqlist);
    return 0;
}
