#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int val_a = *(int*)a;
    int val_b = *(int*)b;
    return abs(val_b) - abs(val_a); // 遞減排序（依時間點）
}

int main(){
    int cnt[10002] = {};          // 儲存所有進出事件，正數為進場，負數為出場
    int n, index = 0;
    scanf("%d", &n);              // 讀入車輛數量

    for (int _ = 0; _ < n; _++){
        int l, r;
        scanf("%d%d", &l, &r);    // 讀入每輛車的進出時間
        cnt[index++] = l;         // 進場記為正數
        cnt[index++] = -r;        // 出場記為負數
    }

    qsort(cnt, 2*n, sizeof(int), cmp); 

    int max = -99999, sum = 0;
    for (int i = 2*n-1; i >= 0; i--){  // 從最早事件往後掃描
        if (cnt[i] > 0) sum++;        // 進場，車輛數 +1
        else if (cnt[i] < 0) sum--;   // 出場，車輛數 -1
        if (sum > max) max = sum;     // 更新最大同時在場車輛數
    }

    printf("%d\n", max);              // 輸出答案
    return 0;
}
