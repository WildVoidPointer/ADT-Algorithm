#include "linked_deque.h"

#include <stdio.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


int main() {

    LinkedDequeEleType test_arr[] = { 3, 5, 4, 7, 8, 9, 2, 5, 5 };
    size_t test_arr_len = sizeof(test_arr) / sizeof(test_arr[1]);


    LinkedDeque* empty_ulim_q = LinkedDeque_create(0, LINKED_DEQUE_UNLIMITED_MODE);
    LinkedDeque_display(empty_ulim_q);
    LinkedDeque_front_dequeue(empty_ulim_q);
    LinkedDeque_rear_dequeue(empty_ulim_q);
    LinkedDeque_clean(&empty_ulim_q);
    printf("LinkedDequeCleanResult: %p\n", empty_ulim_q);


    LinkedDeque* build_of_arr_q = LinkedDeque_build_of_array(
        test_arr_len, test_arr, 30, LINKED_DEQUE_LIMITED_MODE 
    );
    LinkedDeque_display(build_of_arr_q);
    LinkedDeque_clean(&build_of_arr_q);


    LinkedDeque* build_limited_q = LinkedDeque_build_of_array(
        test_arr_len, test_arr, test_arr_len - 3, LINKED_DEQUE_LIMITED_MODE
    );
    LinkedDeque_display(build_limited_q);


    LinkedDeque* build_null_q = LinkedDeque_build_of_array(
        test_arr_len, NULL, test_arr_len - 3, LINKED_DEQUE_LIMITED_MODE
    );
    LinkedDeque_display(build_limited_q);


    LinkedDeque* overflow_test = LinkedDeque_build_of_array(
        test_arr_len, test_arr, test_arr_len, LINKED_DEQUE_LIMITED_MODE
    );
    printf(
        "OverflowTestLinkedDequeInfo: "  \
        "Length: %lu  Size: %lu  IsEmpty: %d  IsFilled: %d  IsLimited: %d\n",
        LinkedDeque_get_length(overflow_test), 
        LinkedDeque_get_size(overflow_test),
        LinkedDeque_is_empty(overflow_test),
        LinkedDeque_is_filled(overflow_test),
        LinkedDeque_is_limited(overflow_test)
    );
    LinkedDeque_rear_enqueue(overflow_test, 233);
    LinkedDeque_front_enqueue(overflow_test, 233);


    LinkedDequeUnit* 
    overflow_test_front_deq_ele = LinkedDeque_front_dequeue(overflow_test);
    LinkedDequeUnit* 
    overflow_test_rear_deq_ele = LinkedDeque_rear_dequeue(overflow_test);
    printf(
        "OverflowTestLinkedDequeDequeueEle: FrontEle: %d  RearEle: %d\n",
        overflow_test_front_deq_ele->data,
        overflow_test_rear_deq_ele->data
    );
    LinkedDeque_display(overflow_test);


    printf(
        "OverflowTestLinkedDequeEnqueueReturnCode: "  \
        "FrontReCode: %d  RearReCode: %d\n",

        LinkedDeque_front_enqueue(overflow_test, 233),
        LinkedDeque_rear_enqueue(overflow_test, 2333)
    );
    LinkedDeque_display(overflow_test);


    LinkedDequeUnit_clean(&overflow_test_front_deq_ele);
    LinkedDequeUnit_clean(&overflow_test_rear_deq_ele);
    printf(
        "OverflowTestLinkedDequeDequeueUnitCleanResult: " \
        "FrontUnit: %p  RearUnit: %p\n",
        overflow_test_front_deq_ele,
        overflow_test_rear_deq_ele
    );
    LinkedDeque_clean(&overflow_test);

    return 0;
}
