#include "linked_stack.h"

#include <stdio.h>


int main() {
    LinkedStackDataType arr[] = {1, 2, 3, 4, 5, 6, 7, 8};

    int arr_len = sizeof(arr) / sizeof (arr[0]);

    LinkedStack* st = LinkedStack_create(arr_len);

    LinkedStackDataType popped;

    LinkedStack_display(st);

    LinkedStack_destroy(&st);

    printf("LinkedStackDestroyResult: %p\n", st);

    st = LinkedStack_create(arr_len);

    for (int i = 0; i < arr_len; i++) {
        LinkedStack_push(st, arr[i]);
    }

    LinkedStack_display(st);

    LinkedStack_push(st, 9);

    LinkedStack_pop(st, &popped);

    printf(
        "PoppedNodeData:  %d,   CurrentLength: %zu\n", 
        popped,
        LinkedStack_length(st)
    );

    LinkedStack_display(st);


    LinkedStack_destroy(&st);

}
