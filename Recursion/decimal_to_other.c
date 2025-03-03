#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 233


void dec_to_other1(int num, int base, char res_buf[], int *res_buff_offset, char place_map[]) {
    int _rem = num % base;
    if (num >= base) {
        dec_to_other1(num / base, base, res_buf, res_buff_offset, place_map);
    }

    res_buf[(*res_buff_offset)++] = place_map[_rem];
}


char* dec_to_other2(int num, int base, char place_map[]) {
    if (num < base) {
       char *_res_buf = (char*)malloc(2 * sizeof(char));
       _res_buf[0] = place_map[num];
       _res_buf[1] = '\0';
       return _res_buf;
    } else {
        char *_temp = dec_to_other2(num / base, base, place_map);
        char _cur_place_map[2] = { place_map[num % base], '\0'};
        char *_res_buf = (char*)malloc((strlen(_temp) + 2) * sizeof(char));
        strcpy(_res_buf, _temp);
        strcat(_res_buf, _cur_place_map);
        free(_temp);
        return _res_buf;
    }
}


int main(int argc, char const *argv[]) {

    char res[MAX_BUFFER] = {0};
    char place_map[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };

    int special_offset = 0;
    char *res_ptr = dec_to_other2(10, 2, place_map);

    for (int i = 0; i < strlen(res_ptr); i++) {
        printf("%c", res_ptr[i]);
    }
    puts("");

    free(res_ptr);

    return 0;
}

