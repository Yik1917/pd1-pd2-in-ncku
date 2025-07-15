#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);         // 讀入記錄總數 N

    int s;
    short check = 0;         // 標記當前是否處於 40–60 區間
    int counter = 0;         // 計算通過閘道次數

    while (scanf("%d", &s) != EOF) {
        if (s <= 60) {
            check = 1;       // 出現速度 ≤ 60，開始一段閘道區間
        }
        if (check == 1 && s > 60) {
            counter++;       // 從閘道區間離開，次數 +1
            check = 0;       // 重置狀態
        }
    }
    if (check == 1)
        counter++;           // 最後若仍在閘道區間，補計一次

    printf("%d\n", counter); // 輸出最小可能的 M 值

    return 0;
}
