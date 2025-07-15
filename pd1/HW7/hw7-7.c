#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hw7-7.h"

extern char all_testcase[59049][11];
static int k = 0;

struct Count {
    char C[200][11];
    int a_cnt, b_cnt, c_cnt;
} H = {{0}};

static void swap_char(char *x, char *y) {
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

// 根據 H.a_cnt, H.b_cnt, H.c_cnt 生成一個原始字串到 H.C[count]
static void StringGenerate(int count) {
    int idx = 0;
    for (int t = 0; t < H.a_cnt; t++, idx++)
        H.C[count][idx] = 'a';
    for (int t = 0; t < H.b_cnt; t++, idx++)
        H.C[count][idx] = 'b';
    for (int t = 0; t < H.c_cnt; t++, idx++)
        H.C[count][idx] = 'c';
    H.C[count][idx] = '\0';
}

// 列舉 a_cnt + b_cnt + c_cnt == len 的所有 (a_cnt,b_cnt,c_cnt)
static void H_Combination(int len) {
    int count = 0;
    for (int i = 0; i <= len; i++) {
        for (int j = 0; i + j <= len; j++) {
            H.a_cnt = i;
            H.b_cnt = j;
            H.c_cnt = len - i - j;
            StringGenerate(count++);
        }
    }
}

// 對字串 s[ index .. len-1 ] 做不重複排列並存入 all_testcase
static void Permutation(char *s, int index, int len) {
    if (index == len - 1) {
        strcpy(all_testcase[k++], s);
        return;
    }
    short used[256] = {0};
    for (int i = index; i < len; i++) {
        unsigned char ch = s[i];
        if (used[ch]) continue;
        used[ch] = 1;
        swap_char(&s[index], &s[i]);
        Permutation(s, index + 1, len);
        swap_char(&s[index], &s[i]);
    }
}

static int compar(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

// 生成所有長度為 len 的由 {'a','b','c'} 組成的字串，並按字典序存入 all_testcase
void GeneratingTest(int len, char all_testcase[][11]) {
    k = 0;
    H_Combination(len);
    for (int i = 0; H.C[i][0] != '\0'; i++) {
        Permutation(H.C[i], 0, len);
    }
    qsort(all_testcase, k, sizeof(all_testcase[0]), compar);
}
