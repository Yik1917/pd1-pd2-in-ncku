#include <stdio.h>

int main()
{
	int a, b;
	scanf("%d%d", &a, &b); // 讀入兩個正整數 a 和 b

	printf("%d", b); // 先印出 b，不換行

	int rem;
	do {
		rem = a % 10;     // 取出 a 的個位數
		printf("%d", rem); // 印出該位數
		a /= 10;           // 去掉 a 的個位數
	} while (a != 0);     // 直到 a 為 0 為止

	printf("\n"); // 最後換行
	return 0;
}
