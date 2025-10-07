#include<stdio.h>
int main(void) {
	char ch,m;
	int a, b, c,weight,all;
	float fee,cost,con,total,last;
	a = b = c = 0;
	ch = getchar();
	
	while (ch  != 'q') {
		switch (ch) {
		case 'a':scanf_s("%d", &weight); a = a + weight;  getchar(); scanf_s("%c", &ch);  break;
		case 'b':scanf_s("%d", &weight); b = b + weight; getchar();  scanf_s("%c", &ch); break;
		case 'c':scanf_s("%d", &weight); c = c + weight; getchar();  scanf_s("%c", &ch); break;
		default:printf("quit%c\n", ch); goto next;
		}
	}
	next: fee = a * 2.05 + b * 1.15 + c * 1.09;
	if (fee > 100) {
		cost = fee * 0.05;
	}
	else {
		cost = 0;
	}
	all = a + b + c;
	if (all <= 5) {
		con = 6.5;
	}
	else if (all > 5 && all <= 20) {
		con = 14;
	}
	else {
		con = 14 + (all - 20) * 0.5;
	}
	last = fee - cost;
	total = fee - cost + con;
	printf("2.05 1.15 1.09\n");
	if (cost == 0) {
		printf("%f %f %f %f\n", fee, last, con, total);
	}
	else {
		printf("%f %f %f %f %f\n", fee, last,cost, con, total);
	}
	return 0;
	
}