#include<stdio.h>
int scores[300][300];
int main(void) {
	int T;
	int n, m, x;
	int c;
	scanf_s("%d", &T);
	int t, i, j;
	for (t = 0; t < T; t++) {
		scanf_s("%d %d %d", &n, &m, &x);
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				scanf_s("%d", &scores[i][j]);
			}   //小S数列为scores[x-1][j]
		}
		scanf_s("%d", &c);

		//先排除不可挽回情况，出现直接up
		int test = 0;
		for (j = 0; j < m; j++) {
			int temp = 0;
			for (i = 0; i < n; i++) {
				if ((i == x - 1) || (i == x - 2))continue;
				else if (scores[i][j] == scores[i + 1][j])temp += 1;
				if ((i == x - 2) && (scores[i][j] == scores[i + 2][j]))temp += 1;
			}
			if (temp == n - 1) {
				printf("up\n");
				test = 1;
				break;
			}

		}

		if (test == 1) {
			int more[300];
			for (i = 0; i < m; i++)more[i] = 0;
			int less[300];
			for (i = 0; i < m; i++)less[i] = 0;
			int flag = 0;

			for (j = 0; j < m; j++) {
				for (i = 0; i < n; i++) {
					if (i == x - 1)continue;
					else if (scores[x - 1][j] < scores[i][j]) {
						more[j] += 1; //有比小S答案更大的数
					}
					else if (scores[x - 1][j] > scores[i][j]) {
						less[j] += 1; //有比小S答案更小的数
					}
				}
				if ((more[j] == 0) || (less[j] == 0)) {
					flag += 1;
				}

			}

			if (flag > c) {
				printf("up\n");
			}
			else {
				printf("down\n");
			}
		}



	}
	return 0;
}