#include <stdio.h>

int main()
{
	int N;
	scanf("%d", &N); // 讀入整數 N

	int rem;
	short check = 0; // 是否已開始印出（用來跳過前導 0）

	do {
		rem = N % 10;  // 取出個位數
		N /= 10;       // 把個位數去掉

		if (rem != 0)
			check = 1; // 出現第一個非零數字後就開始印

		if (check)
			printf("%d", rem); // 印出反轉後的數字
	} while (N != 0); // 繼續直到 N 為 0

	printf("\n"); // 換行
	return 0;
}
