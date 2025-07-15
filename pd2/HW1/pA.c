#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define START 0
#define END 1
#define FAILURE 0
#define SUCCESS 1

char s1[200001], s2[200001];
int main()
{
    // 讀入兩個字串
    scanf("%s%s", s1, s2);
    int q; 
    scanf("%d", &q);                  // 讀入查詢數量
    int len = strlen(s1);
    int table[26];
    srand((unsigned)time(NULL));      // 隨機種子

    // 建立每個字母對應的隨機值
    for (int i = 0; i < 26; i++)
        table[i] = rand();

    int sums1[200001], sums2[200001];
    sums1[0] = 0; 
    sums2[0] = 0;
    long long sum1 = 0, sum2 = 0;
    // 計算前綴和
    for (int i = 0; i < len; i++){
        sum1 += table[s1[i]-'a'];
        sums1[i+1] = sum1;
        sum2 += table[s2[i]-'a'];
        sums2[i+1] = sum2;
    }
    // 處理每個查詢
    for (int i = 0; i < q; i++){
        int index[2][2];
        scanf("%d%d%d%d", 
            &index[0][START], &index[0][END], 
            &index[1][START], &index[1][END]);
        // 長度不同直接 NO
        if (index[0][END] - index[0][START] 
          != index[1][END] - index[1][START]){
            puts("NO");
            continue;
        }
        // 比較對應區間
        if (sums1[index[0][END]] - sums1[index[0][START]-1] 
          == sums2[index[1][END]] - sums2[index[1][START]-1])
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
