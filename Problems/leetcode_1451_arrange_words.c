/* 
From: 
    https://leetcode.com/problems/rearrange-words-in-a-sentence/description/


Description:
    Given a sentence text (A sentence is a string of space-separated words) in the following format:

    First letter is in upper case.
    Each word in text are separated by a single space.
    Your task is to rearrange the words in text such that all words are rearranged in an increasing order of their lengths. If two words have the same length, arrange them in their original order.

    Return the new text following the format shown above.


Example 1:
    Input: text = "Leetcode is cool"

    Output: 
        "Is cool leetcode"

    Explanation: 
        There are 3 words, "Leetcode" of length 8, "is" of length 2 and "cool" of length 4.
        Output is ordered by length and the new first word starts with capital letter.


Example 2:
    Input: text = "Keep calm and code on"

    Output: "On and keep calm code"

    Explanation: 
        Output is ordered as follows:
            "On" 2 letters.
            "and" 3 letters.
            "keep" 4 letters in case of tie order by position in original text.
            "calm" 4 letters.
            "code" 4 letters.

Example 3:
    Input: 
        "To be or not to be"
        
    Output: 
        "To be or to be not"
 

Constraints:
    text begins with a capital letter and then contains lowercase letters and single space between words.
    1 <= text.length <= 10^5
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* word;
    size_t len;
} Word;

Word* WORDS[100000];


void merge(Word* arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Word* leftArr[n1];
    Word* rightArr[n2];

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i]->len <= rightArr[j]->len) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
}


void merge_sort(Word* arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


char* concat_words(Word* arr[], int n) {

    size_t total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += arr[i]->len + 1;
    }

    char* result = (char*)malloc(total_length * sizeof(char));

    result[0] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(result, arr[i]->word);
        if (i < n - 1) {
            strcat(result, " ");
        }
    }

    return result;
}


char* arrange_words(char* text) {
    text[0] += 32;
    size_t length = strlen(text);
    int words_index = 0;

    char* start = text;
    char* end = NULL;
    for (int i = 0; i < length; i++) {
        if (text[i] == ' ') {
            WORDS[words_index] = (Word*) malloc(sizeof(Word));
            size_t word_len = &text[i] - start;
            WORDS[words_index]->word = (char*) malloc((word_len + 1) * sizeof(char));
            strncpy(WORDS[words_index]->word, start, word_len);
            WORDS[words_index]->word[word_len] = '\0';
            WORDS[words_index]->len = word_len;
            words_index++;
            start = &text[i + 1];
        }
    }

    if (start < text + length) {
        size_t last_word_len = text + length - start;
        WORDS[words_index] = (Word*) malloc(sizeof(Word));
        WORDS[words_index]->word = (char*) malloc((last_word_len + 1) * sizeof(char));
        strncpy(WORDS[words_index]->word, start, last_word_len);
        WORDS[words_index]->word[last_word_len] = '\0';
        WORDS[words_index]->len = last_word_len;
        words_index++;
    }

    merge_sort(WORDS, 0, words_index - 1);

    char* result = concat_words(WORDS, words_index);
    result[0] -= 32;
    return result;
}


int main(int argc, char const *argv[]) {
    char text[] = "Leetcode is cool";
    printf("%s\n", arrange_words(text));
    return 0;
}
