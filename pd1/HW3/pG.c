#include <stdio.h>
#include <limits.h>

int main(){
    long long a, b;
    scanf("%lld%lld", &a, &b); // 讀入兩個 long long 整數

    if (a > 0) {
        if (b <= 0)
            printf("No\n"); // a > 0, b <= 0，不會溢位
        else {
            if (LLONG_MAX - a >= b)
                printf("No\n"); // 相加不會超過最大值
            else
                printf("Yes\n"); // 相加會超過最大值，發生溢位
        }
    } else if (a < 0) {
        if (b >= 0)
            printf("No\n"); // a < 0, b >= 0，不會溢位
        else {
            if (LLONG_MIN - a <= b)
                printf("No\n"); // 相加不會小於最小值
            else
                printf("Yes\n"); // 相加會小於最小值，發生溢位
        }
    } else
        printf("No\n"); // a == 0，無論 b 是多少都不會溢位

    return 0;
}
