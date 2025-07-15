#include <stdio.h>

int main()
{
	int a, b, c;
	scanf("%d-%d-%d", &a, &b, &c); // 以 a-b-c 格式讀入三個數字（用 - 分隔）

	int sum = 0; // 總獎金初始化為 0

	if (a == b && a == c)
		sum += 300; // 三個數相同，加 300 元
	if (a == c)
		sum += 100; // a 跟 c 相同，加 100 元
	if (a + b < c)
		sum += 150; // a + b 小於 c，加 150 元
	if (a < b)
		sum += 50; // a 小於 b，加 50 元

	printf("%d\n", sum); // 輸出總獎金

	return 0;
}
