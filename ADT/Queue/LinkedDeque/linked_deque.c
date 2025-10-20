#include "linked_deque.h"

#include <stdio.h>
#include <stdlib.h>


LinkedDeque* LinkedDeque_create(size_t size, LinkedDequeLimitedModeEnum mode) {
    LinkedDeque* q = (LinkedDeque*) malloc (sizeof(LinkedDeque));
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_CREATE_ERROR);
        return NULL;
    }

    if (mode == LINKED_DEQUE_LIMITED_MODE) {
        q->is_limited = 1;
        q->size = size;
    } else if (mode == LINKED_DEQUE_UNLIMITED_MODE) {
        q->is_limited = 0;
    } else {
        fprintf(stderr, LINKED_DEQUE_CREATE_EXCEPTION);
        LinkedDeque_clean(&q);
        return NULL;
    }

    q->front = q->rear = NULL;
    q->length = 0;
    return q;
}


LinkedDeque* LinkedDeque_build_of_array(
    size_t len, LinkedDequeEleType* arr, 
    size_t size, LinkedDequeLimitedModeEnum mode
) {
    if (arr ==  NULL) {
        fprintf(stderr, LINKED_DEQUE_BUILD_EXCEPTION);
        return NULL;
    }

    LinkedDeque* q = LinkedDeque_create(size, mode);

    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_BUILD_ERROR);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (LinkedDeque_rear_enqueue(q, arr[i]) == -1) {
            LinkedDeque_clean(&q);
            fprintf(stderr, LINKED_DEQUE_BUILD_ERROR);
            return NULL;
        }
    }

    return q;
}


int LinkedDeque_is_empty(LinkedDeque* q) {
    return (q == NULL || q->front == NULL);
}


int LinkedDeque_is_filled(LinkedDeque* q) {
    return (
        q != NULL && q->is_limited && q->length >= q->size
    );
}


int LinkedDeque_is_limited(LinkedDeque* q) {
    return (q != NULL) ? q->is_limited : -1;
}


ssize_t LinkedDeque_get_size(LinkedDeque* q) {
    return (
        q != NULL && q->is_limited
    ) ? q->size : -1;
}


ssize_t LinkedDeque_get_length(LinkedDeque* q) {
    return (q != NULL) ? q->length : -1;
}


LinkedDequeUnit* LinkedDeque_front(LinkedDeque* q) {
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return NULL;
    }

    LinkedDequeUnit* buf = LinkedDequeUnit_create(&(q->front->data));

    if (buf == NULL) {
        fprintf(stderr, LINKED_DEQUE_UNIT_BUFFER_CREATE_ERROR);
        return NULL;
    }

    buf->next = buf->prev = NULL;

    return buf;
}


LinkedDequeUnit* LinkedDeque_rear(LinkedDeque* q) {
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return NULL;
    }

    LinkedDequeUnit* buf = LinkedDequeUnit_create(&(q->rear->data));

    if (buf == NULL) {
        fprintf(stderr, LINKED_DEQUE_UNIT_BUFFER_CREATE_ERROR);
        return NULL;
    }

    buf->next = buf->prev = NULL;

    return buf;
}


LinkedDequeUnit* LinkedDeque_front_dequeue(LinkedDeque* q) {
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return NULL;
    }

    if (LinkedDeque_is_empty(q)) {
        fprintf(stderr, LINKED_DEQUE_DEQUEUE_EXCEPTION);
        return NULL;
    }

    LinkedDequeUnit* ele = q->front;
    q->front = q->front->next;
    
    if (LinkedDeque_is_empty(q)) {
        q->rear = NULL;
    } else {
        q->front->prev = NULL;
    }
    
    q->length--;
    ele->next = ele->prev = NULL;
    return ele;
}


LinkedDequeUnit* LinkedDeque_rear_dequeue(LinkedDeque* q) {
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return NULL;
    }

    if (LinkedDeque_is_empty(q)) {
        fprintf(stderr, LINKED_DEQUE_DEQUEUE_EXCEPTION);
        return NULL;
    }

    LinkedDequeUnit* ele = q->rear;
    q->rear = q->rear->prev;
    
    if (LinkedDeque_is_empty(q)) {
        q->front = NULL;
    } else {
        q->rear->next = NULL;
    }
    
    q->length--;
    ele->next = ele->prev = NULL;
    return ele;
}


int LinkedDeque_front_enqueue(LinkedDeque* q, LinkedDequeEleType data) {
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    if (LinkedDeque_is_filled(q)) {
        fprintf(stderr, LINKED_DEQUE_ENQUEUE_EXCEPTION);
        return -1;
    }

    LinkedDequeUnit* new_unit = LinkedDequeUnit_create(&data);

    if (new_unit == NULL) {
        fprintf(stderr, LINKED_DEQUE_ENQUEUE_FAILED_ERROR);
        return -1;
    }

    if (LinkedDeque_is_empty(q)) {
        q->front = q->rear = new_unit;
    } else {
        q->front->prev = new_unit;
        new_unit->next = q->front;
        q->front = new_unit;
    }

    q->length++;
    return 0;
}


int LinkedDeque_rear_enqueue(LinkedDeque* q, LinkedDequeEleType data) {
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    if (LinkedDeque_is_filled(q)) {
        fprintf(stderr, LINKED_DEQUE_ENQUEUE_EXCEPTION);
        return -1;
    }

    LinkedDequeUnit* new_unit = LinkedDequeUnit_create(&data);

    if (new_unit == NULL) {
        fprintf(stderr, LINKED_DEQUE_ENQUEUE_FAILED_ERROR);
        return -1;
    }

    if (LinkedDeque_is_empty(q)) {
        q->front = q->rear = new_unit;
    } else {
        q->rear->next = new_unit;
        new_unit->prev = q->rear;
        q->rear = new_unit;
    }

    q->length++;
    return 0;
}


int LinkedDeque_display(LinkedDeque* q) {
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    LinkedDequeUnit* current = q->front;

    printf("LinkedDeque: {  ");
    while (current != NULL) {
        printf("%d  ", current->data);
        current = current->next;
    }
    printf("}\n");

    return 0;
}


int LinkedDeque_clean(LinkedDeque** q) {
    if (q == NULL || *q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    LinkedDequeUnit* tmp_unit = NULL;

    while (!LinkedDeque_is_empty(*q)) {
        tmp_unit = LinkedDeque_front_dequeue(*q);
        LinkedDequeUnit_clean(&tmp_unit);
    }

    free(*q);
    *q = NULL;
    return 0;
}


LinkedDequeUnit* LinkedDequeUnit_create(LinkedDequeEleType* data) {
    LinkedDequeUnit* unit = (LinkedDequeUnit*) malloc (sizeof(LinkedDequeUnit));

    if (unit == NULL) {
        fprintf(stderr, LINKED_DEQUE_UNIT_CREATE_ERROR);
        return NULL;
    }

    if (data == NULL) {
        unit = NULL;
    } else {
        unit->data = *data;
        unit->next = unit->prev = NULL;
    }

    return unit;
}


int LinkedDequeUnit_clean(LinkedDequeUnit** unit) {
    free(*unit);
    *unit = NULL;
    return 0;
}
