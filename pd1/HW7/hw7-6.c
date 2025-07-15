#include <stdio.h>
#include <string.h>
#include "hw7-6.h"

char *ProcessingCommand(char string1[][21], char string2[][21],
                       char *final, int command_cnt, int test_mode)
{
    char testcase[51];
    strcpy(testcase, final);  // 把輸入字串複製到 testcase

    if (test_mode == 1) {
        int i = 0;
        while (i < command_cnt) {
            char *target = strstr(testcase, string1[i]);  // 找到第 i 條指令的目標子串
            char output[51] = {};

            if (target != NULL) {
                int j = 0;
                // 複製 target 之前的內容
                for (char *p = testcase; p < target; p++)
                    output[j++] = *p;

                // 接上替換字串
                strcat(output, string2[i]);
                // 接上原子串 target 後面剩餘的部分
                strcat(output, target + strlen(string1[i]));

                i = 0;  // 重新從第一條指令開始檢查
                strcpy(testcase, output);  // 更新 testcase
                printf("%s\n", output);    // 印出每一步結果
            } else {
                i++;  // 沒找到就檢查下一條指令
            }
        }
        // 最終結果存回 string1[50]，並回傳此指標
        strcpy(string1[50], testcase);
        return string1[50];
    }
    return final;
}
