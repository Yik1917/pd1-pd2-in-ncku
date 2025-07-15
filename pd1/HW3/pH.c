#include <stdio.h>
#include <stdlib.h>

// 將 a 與 b 逐位相加，結果存入 digit 陣列（低位在前）
void add(long long a, long long b, int digit[])
{
    int rem_a, rem_b;
    int upper = 0;       // 進位
    short counter = 0;   // 目前處理的位數索引

    do {
        rem_a = abs(a % 10);  // 取 a 的當前位絕對值
        rem_b = abs(b % 10);  // 取 b 的當前位絕對值
        a /= 10; b /= 10;     // 去掉已處理的最低位

        // 計算該位結果與進位
        digit[counter] = (rem_a + rem_b + upper) % 10;
        upper = (rem_a + rem_b + upper) / 10;
        counter++;
    } while (a != 0 || b != 0);

    digit[counter] = upper;  // 處理最後的進位
}

// 從高位到低位印出 digit 陣列中的數字，跳過前導零
void print_array(int digit[])
{
    short check = 0;  // 是否已開始印出（遇到第一個非零位）
    for (int i = 19; i >= 0; i--) {
        if (digit[i] != 0)
            check = 1;
        if (check)
            printf("%d", digit[i]);
    }
}

int main()
{
    long long a, b;
    scanf("%lld%lld", &a, &b);  // 讀入兩個 long long 整數

    // 異號相加可直接用內建，否則用手動逐位相加
    short pos_neg = (a >= 0 && b <= 0) || (a <= 0 && b >= 0);
    int digit[20] = {0};

    if (pos_neg) {
        // 異號或其中有零，直接相加並輸出
        printf("%lld", a + b);
    } else {
        // 同號，用手動加法
        add(a, b, digit);

        if (a > 0)
            print_array(digit);  // 正數結果
        if (a < 0) {
            printf("-");        
            print_array(digit);  // 負數結果，加負號
        }
    }

    printf("\n");  // 換行
    return 0;
}
