#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);                // 讀入車輛數量 n
    int cnt[1001] = {};             // 每個時間點車輛計數器，初始化為 0

    for (int _ = 0; _ < n; _++){
        int l, r;
        scanf("%d%d", &l, &r);      // 讀入進出時間 l, r
        for (int i = l; i < r; i++){
            cnt[i]++;               // 在 [l, r) 時間段內每點加一輛車
        }
    }

    int max = -1;                   // 用來記錄最大同時在場車輛數
    for (int i = 1; i < 1001; i++){
        if (cnt[i] > max)
            max = cnt[i];           // 更新最大值
    }

    printf("%d\n", max);            // 輸出最大同時在場車輛數
    return 0;
}
