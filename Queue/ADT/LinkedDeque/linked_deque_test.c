#include "linked_deque.h"
#include <stdio.h>


int main() {
    LinkedDeque* q = LinkedDeque_create(0, LINKED_DEQUE_UNLIMITED_MODE);
    LinkedDeque_clean(&q);
}
