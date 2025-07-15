#include <stdio.h>

int main()
{
    int n, q, k;
    scanf("%d%d%d", &n, &q, &k);       // 讀入車輛數 n、查詢數 q、限制人數 k

    int S[100001] = {};                // S[i] 表示前 i 輛車中違規車輛的累計數量
    int quantity, counter = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &quantity);        // 讀入第 i 輛車的人數
        if (quantity < k)              // 若人數不足，計為違規
            counter++;
        S[i] = counter;                // 存入目前為止的違規總數
    }

    int start, end;
    for (int _ = 0; _ < q; _++) {
        scanf("%d%d", &start, &end);   // 查詢區間 [start, end]
        printf("%d\n", S[end] - S[start - 1]); // 區間違規車輛數
    }

    return 0;
}
