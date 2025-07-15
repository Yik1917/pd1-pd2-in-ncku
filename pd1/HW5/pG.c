#include <stdio.h>
#include <stdlib.h>

// 計算函數 f(x, y, z)
int compute(int x, int y, int z)
{
    return ((x + z) ^ (y - z)) - (x & z & (y & 2024) | (abs(z - y)));
}

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);       // 讀入 a, b, c 三個數字

    int result[6] = {};                // 存放所有排列的結果
    short i = -1;
    result[++i] = compute(a, b, c);
    result[++i] = compute(a, c, b);
    result[++i] = compute(b, a, c);
    result[++i] = compute(b, c, a);
    result[++i] = compute(c, a, b);
    result[++i] = compute(c, b, a);

    int max = -99999;
    for (int j = 0; j < 6; j++) {      // 找出最大值
        if (result[j] > max)
            max = result[j];
    }

    printf("%d\n", max);              // 輸出最大值
    return 0;
}
