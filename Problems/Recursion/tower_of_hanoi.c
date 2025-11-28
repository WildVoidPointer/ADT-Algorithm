#include <stdio.h>


typedef struct {
    int* disks;
    int num ;
} Pillar;


static void move_disk(Pillar* src, Pillar* dest) {
    dest->disks[dest->num++] = src->disks[src->num - 1];
    src->num--;
}


static int pillar_is_empty(Pillar* p) {
    return p->num <= 0;
}


static int is_tower_of_hanoi(Pillar* p) {
    for (int i = 0; i < p->num - 1; i++) {
        if (p->disks[i + 1] < p->disks[i]) {
            return 0;
        }
    }
    return 1;
}


static void move_to_dest(
    int n,              // 需要移动的圆盘数量
    Pillar* src,        // 源柱
    Pillar* help,       // 辅助柱
    Pillar* dest        // 目标柱
) {

    if (n == 1) {
        move_disk(src, dest);
        return;
    }

    // 1. 将上面 N-1 个圆盘从 源柱(src) 移到 辅助柱(help)
    move_to_dest(n - 1, src, dest, help);

    // 2. 将第 N 个圆盘（最大的，即 src 柱子最底下的那个）
    // 从 源柱(src) 移到 目标柱(dest)
    move_disk(src, dest);

    // 3. 将 N-1 个圆盘从 辅助柱(help) 移到 目标柱(dest)
    move_to_dest(n - 1, help, src, dest);
}


static void pillar_println(Pillar* p) {
    for (int i = 0; i < p->num; i++) {
        printf("%d  ", p->disks[i]);
    }
    putc('\n', stdout);
}


int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    const int size = sizeof(arr) / sizeof(arr[0]);

    int help_arr[size];

    int dest_arr[size];

    Pillar src = {.disks = arr, .num = size};

    Pillar help = {.disks = help_arr, .num = 0};

    Pillar dest = {.disks = dest_arr, .num = 0};

    if (is_tower_of_hanoi(&src)) {
        move_to_dest(size, &src, &help, &dest);
        pillar_println(&dest);
    }
}
