#include <stdio.h>
#include <stdbool.h>

int main()
{
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c); // 讀入三個數字

	bool check = false; // 是否有缺數字

	if (a != 1 && b != 1 && c != 1) {
		check = true;
		printf("1"); // 如果沒有 1，就輸出 1
	}
	if (a != 2 && b != 2 && c != 2) {
		if (check)
			printf(" "); // 如果前面已經有輸出過，先印空格
		check = true;
		printf("2"); // 沒有 2 就輸出 2
	}
	if (a != 3 && b != 3 && c != 3) {
		if (check)
			printf(" ");
		check = true;
		printf("3"); // 沒有 3 就輸出 3
	}
	if (check)
		printf("\n"); // 有輸出缺數，最後換行
	else
		printf("Oh, Fried Shrimp, you're amazing!\n"); // 如果都沒缺，誇獎炸蝦！

	return 0;
}
