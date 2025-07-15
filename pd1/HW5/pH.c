#include <stdio.h>

int H[2000][2000];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);        // 讀入網格大小 n(行) 和 m(列)

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &H[i][j]); // 讀入每個位置的建築高度

    int ns_skylines[m], ew_skylines[n];

    // 計算每列的北-南方向天際線（每列最高值）
    for (int i = 0; i < m; i++) {
        int max = -1;
        for (int j = 0; j < n; j++)
            if (H[j][i] > max)
                max = H[j][i];
        ns_skylines[i] = max;      // 存入第 i 列的最高高度
    }

    // 計算每行的東-西方向天際線（每行最高值）
    for (int i = 0; i < n; i++) {
        int max = -1;
        for (int j = 0; j < m; j++)
            if (H[i][j] > max)
                max = H[i][j];
        ew_skylines[i] = max;      // 存入第 i 行的最高高度
    }

    long sum_dif = 0;
    // 遍歷每個格子，按可增到的最大高度減去原高，累加增量
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            long min_skyline = (ew_skylines[i] < ns_skylines[j])
                                ? ew_skylines[i] 
                                : ns_skylines[j];
            sum_dif += min_skyline - H[i][j];
        }
    }

    printf("%ld\n", sum_dif);     // 輸出總共能增加的高度和
    return 0;
}
