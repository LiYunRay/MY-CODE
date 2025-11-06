#include<stdio.h>
long long max(long long, long long);
long long fin[1000];
int  t[10000], c[10000], p[10000];
int main(void) {
	int t1, t2, a, b, i, time, exp;
	scanf_s("%d:%d", &a, &b);

	t1 = 60 * a + b;
	scanf_s("%d:%d", &a, &b);
	t2 = 60 * a + b;
	int remain = t2 - t1;
	int n;
	for (i = 0; i < remain; i++) {
		fin[i] = 0;
	}
	scanf_s("%d", &n);
	 
	for (i = 0; i < n; i++) {
		scanf_s("%d %d %d",&t[i], & c[i], &p[i]);
	}
	for (i = 0; i < n; i++) {
		if (p[i] == 0) {
			if (t[i] <= remain) {
				fin[t[i] - 1] = max(fin[t[i] - 1], c[i]);
			}
			for (time = t[i]; time < remain; time++) {
				fin[time] = max(fin[time], fin[time - t[i]] + c[i]);
			}
		}
		else {
			exp = 1;
			while (p[i] >=exp) {
					for (time = remain - 1; time >= t[i]*exp; time--) {
						fin[time] = max(fin[time], fin[time - t[i] * exp] + c[i] * exp);
					}
					if (t[i] * exp <= remain) {
						fin[t[i] * exp - 1] = max(fin[t[i] * exp - 1], c[i] * exp);
					}
					
				p[i] -= exp;
				exp *= 2;

			}
			if (p[i] != 0) {
				for (time = remain - 1; time >= p[i] * t[i]; time--) {
					fin[time] = max(fin[time], fin[time - p[i] * t[i]] + c[i] * p[i]);
				}
				if (p[i]*t[i] <= remain) {
					fin[p[i] * t[i] - 1] = max(fin[p[i] * t[i] - 1], c[i] * p[i]);
				}
			}
		}



	}
	printf("%lld", fin[remain - 1]);
	return 0;

	
}
long long max(long long a, long long b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}