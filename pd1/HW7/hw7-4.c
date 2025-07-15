#include <stdio.h>
#include <string.h>
#include "hw7-4.h"

char *getAnswer1(char *testcase)
{
    char *s = testcase;       // 指標指向輸入字串
    char answer[51] = {};     
    int k = 0;                // answer 陣列索引

    while (*s != '\0') {
        int len_na = strcspn(s, "a"); // 找到第一個 'a' 之前的長度
        if (len_na != 0) {
            // 複製非 'a' 的字元
            for (int i = 0; i < len_na; i++)
                answer[k++] = *(s + i);
            s += len_na;
        } else {
            int len_a = strspn(s, "a"); // 連續 'a' 的長度
            if (len_a == 1)
                answer[k++] = *(s++);   // 單個 'a' 保留
            else
                s += len_a;             // 多個 'a' 刪除
        }
    }

    strcpy(testcase, answer);  // 將結果拷回 testcase
    return testcase;           // 回傳修改後的字串
}
