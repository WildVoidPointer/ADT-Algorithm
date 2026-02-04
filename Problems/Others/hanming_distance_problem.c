#include <stdio.h>


static void hanming_distance_dfs(
    char s[], int n, int h, int pos, int total
) {

    if (pos == n) {

        if (total == h) {
            s[n] = '\0';
            printf("%s\n", s);
        }

        return;
    }

    if (total + (n - pos) < h) {
        return;
    }


    if (total > h) {
        return;
    }

    // first set the pos to 0
    s[pos] = '0';
    hanming_distance_dfs(s, n, h, pos + 1, total);

    // then set the pos to 1
    if (total + 1 <= h) {
        s[pos] = '1';
        hanming_distance_dfs(s, n, h, pos + 1, total + 1);
        s[pos] = '0';
    }

}


int main() {
    char s[] = "0000";

    int n = 4;

    int h = 2;

    hanming_distance_dfs(s, n, h, 0, 0);
}