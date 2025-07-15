#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);                 // 讀入元素個數 N

    int k;
    long sum = 0, S[200001] = {};    // sum 累加前綴和，S 存放前綴和陣列

    for (int i = 1; i <= N; i++) {
        scanf("%d", &k);             // 讀入第 i 個元素
        sum += k;                    // 更新累加和
        S[i] = sum;                  // 存入前綴和陣列
    }

    int Q;
    scanf("%d", &Q);                 // 讀入查詢次數 Q
    int start, end;
    for (int _ = 0; _ < Q; _++) {
        scanf("%d%d", &start, &end);             // 讀入查詢範圍 [start, end]
        printf("%ld\n", S[end] - S[start - 1]);  // 前綴和差即為區間和
    }

    return 0;
}
