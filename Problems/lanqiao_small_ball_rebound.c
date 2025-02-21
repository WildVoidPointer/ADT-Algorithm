/* 
From:
    https://www.lanqiao.cn/

Description:
    There is a rectangle with a length of 343,720 units and a width of 233,333 units. 
    Inside the rectangle, at the top-left corner, there is a small ball (its volume can be ignored).
    The initial velocity of the ball is shown in the diagram, and it maintains a constant speed. 
    The velocity components in the length and width directions are in a ratio of 𝑑𝑥:𝑑𝑦=15:17
    When the ball hits the edge of the rectangle, it bounces off, 
    with the angle of incidence equal to the angle of reflection. 
    Therefore, the ball changes direction 
    while maintaining the same speed (if the ball exactly hits a corner, it will return along the same path). 
    How far does the ball travel from the starting point until it reaches the top-left corner for the first time? 
    The answer should be rounded to two decimal places.


Answer:
    1100325199.77
*/


#include <stdio.h>
#include <math.h>


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int lcm(int a, int b) {
    return a * b / gcd(a, b);
}


double return_origin_time1(int speed_x, int speed_y, int width, int height) {

    int time = 1;
    double res = 0;
    int scaled_width = width * 2;
    int scaled_height = height * 2;
    
    while (1) {
        if ((speed_x * time) % scaled_width == 0 && (speed_y * time) % scaled_height == 0) {
            break;
        }
        time++;
    }

    res = sqrt(pow(speed_x * time, 2) + pow(speed_y * time, 2));

    printf("%.2f\n", res);
    return res;
}


double return_origin_time2(int speed_x, int speed_y, int width, int height) {

    double res = 0;
    int scaled_width = width * 2;
    int scaled_height = height * 2;

    int units_time  = lcm(speed_x, scaled_width) / speed_x;

    for (int time = units_time; ; time += units_time) {
        if ((time * speed_y) % scaled_height == 0) {
            res = sqrt((pow((time * speed_x), 2) + (pow((time * speed_y), 2))));
            break;
        }
    }
    printf("%.2f\n", res);
    return res;
}


int main(int argc, char const *argv[]) {
    return_origin_time2(15, 17, 343720, 233333);
    return 0;
}
