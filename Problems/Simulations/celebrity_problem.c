/* 
Description:
    You are in a party with n people. Among them, there might be one celebrity. A celebrity 
    is a person who is known by everyone else in the party but does not know anyone. Everyone 
    else at the party knows at least one person.
    Your task is to find the celebrity. You are given a function knows(a, b) which returns 
    true if person a knows person b, and false otherwise. The people are numbered from 0 to n-1.
    Write an algorithm to find the celebrity. The algorithm should return the index of the celebrity. 
    If there is no celebrity, return -1.

    A person does not know themselves. knows(a, a) will always be false.
    There can be at most one celebrity.


Example 1:
    Input:
        n = 3
        knows matrix: {
            {0, 1, 0},
            {0, 0, 0},
            {1, 1, 0}
        }

    Explanation 1:
        knows(0, 1) is true, so person 0 knows person 1.
        knows(1, 0) is false, knows(1, 2) is false. Person 1 knows no one.
        knows(2, 0) is true, knows(2, 1) is true. Person 2 knows person 0 and 1.
        In this example, person 1 is the celebrity. 
        Everyone else (0 and 2) knows 1, and 1 knows no one.

    Output:
        1


Example 2:
    Input:
        n = 3
        knows matrix: {
            {0, 1, 0},
            {0, 0, 1},
            {1, 0, 0}
        }
        
    Explanation 2:
        Person 0 knows 1.
        Person 1 knows 2.
        Person 2 knows 0.
        No one is known by everyone else, and no one knows no one.
    
    Output:
        -1
*/


#include <stdio.h>


int knows(
    int num, int knows_mtx[num][num], 
    int people1, int people2
) {
    return knows_mtx[people1][people2];
}


int has_celebrity(int num, int knows_mtx[num][num]) {
    int candidate = 0;

    for (int curr = 0; curr < num; curr++) {
        if (knows(num, knows_mtx, candidate, curr)) {
            candidate = curr;
        }
    }

    for (int i = 0; i < num; i++) {
        if (i != candidate) {
            if (
                ! knows(num, knows_mtx, i, candidate) || 
                knows(num, knows_mtx, candidate, i)
            ) {
                return -1;
            }
        }
    }

    return candidate;
}


int main() {
    int num = 3;

    int knows_mtx_with_celebrity[][3] = {
        {0, 1, 0},
        {0, 0, 0},
        {1, 1, 0}
    };

    int knows_mtx_no_celebrity[][3] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    };

    printf(
        "%d\n",
        has_celebrity(num, knows_mtx_with_celebrity)
    );

    printf(
        "%d\n",
        has_celebrity(num, knows_mtx_no_celebrity)
    );

    return 0;
}