#include <stdio.h>


void search_forward_first_great_element(int queue[], int size, int res[]) {
    int stack[size];
    int top = -1;

    for (int i = size - 1; i >= 0; i--) {
        while (top >= 0 && queue[stack[top]] <= queue[i]) {
            top--;
        }

        res[i] = (top >= 0) ? queue[stack[top]] : -1;
        stack[++top] = i;
    }
}


void search_forward_first_less_element(int queue[], int size, int res[]) {
    int stack[size];
    int top = -1;

    for (int i = 0; i < size; i++) {
        while (top >= 0 && queue[stack[top]] >= queue[i]) {
            top--;
        }

        res[i] = (top >= 0) ? queue[stack[top]] : -1;
        stack[++top] = i;
    }
}


void search_sliding_window_max_element(int arr[], int r_size, int w_size, int res[]) {
    int deq[w_size];
    int front = 0, rear = 0;

    for (int i = 0; i < r_size; i++) {
        while (front != rear && arr[deq[rear - 1]] <= arr[i]) {
            rear = (rear + w_size - 1) % w_size;
        }
        
        deq[rear] = i;
        rear = (rear + w_size + 1) % w_size;

        if (deq[front] <= i - w_size) {
            front = (front + w_size + 1) % w_size;
        }

        if (i >= w_size - 1) {
            res[i - w_size + 1] = arr[deq[front]];
        }
    }
}



int main() {
    int queue[] = {1, 2, 2, 5, 4, 7, 7, 8};
    int size = sizeof(queue) / sizeof(queue[0]);
    int res[size - 4 + 1];

    // search_forward_first_element3(queue, size, res);
    search_sliding_window_max_element(queue, size, 4, res);

    for (int i = 0; i < size - 4 + 1; i++) {
        printf("%d  ", res[i]);
    }
    puts("");

    return 0;
}
