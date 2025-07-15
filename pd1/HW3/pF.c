#include <stdio.h>

int main()
{
	int m;
	scanf("%d", &m); // 讀入魔法門檻 m

	int k, sum = 0;          // sum 為目前總魔法指數
	short check = 0, counter = 0; // check 是否已變美味，counter 計數倒幾次醬油

	while (scanf("%d", &k) != EOF) { // 不斷讀入 k（每次倒醬油）
		sum += k;     // 增加魔法指數
		counter++;    // 計數器加一

		if (sum > m) {        // 如果魔法值超過門檻
			if (!check) {     // 且還沒變美味
				printf("Fried Pork!!!!\n"); // 印出提示
				printf("%hd\n", counter);   // 印出倒醬油次數
				check = 1;   // 標記已變美味，之後不再印
			}
		}
	}
	return 0;
}
