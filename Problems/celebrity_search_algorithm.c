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
    n = 3
    knows matrix: [
        [false, true, false],
        [false, false, false],
        [true, true, false]
    ]


Example 2:
    
*/