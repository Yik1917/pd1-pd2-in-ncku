#include <stdio.h>

int main()
{
	int n, c, k;
	scanf("%d%d%d", &n, &c, &k); // 讀入炸蝦數量 n、糖果數量 c、要查詢的編號 k

	int must = c / n, limit = c % n; // 每隻至少分到 must 顆糖；還有 limit 顆剩下來
	int candy = must; // 目前 k 這隻炸蝦至少有 must 顆糖

	if (limit == 0){
		// 如果糖剛好分完，沒有剩，就直接輸出
		printf("%d\n", candy);
		return 0;
	}

	if (must % 2 == 1)
		k = n + 1 - k; // 如果已經分了奇數圈（方向是反的），要反轉炸蝦位置

	if (k <= limit)
		candy++; // 如果這隻炸蝦在下一輪的前 limit 位，會多拿 1 顆糖

	printf("%d\n", candy); // 輸出 k 號炸蝦總共拿到的糖
	return 0;
}
