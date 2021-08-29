#include "../include/head.h"
#include <stdio.h>

void Top() {
	char name[50];
	unsigned long info[2] = {0, 0};
	FILE * fp;

	printf("暂未开发\n");
	Input();
	fp = fopen("top.txt","r");
	if (!fp) {
		printf("存档不存在");
		Input();
		return;
	}
	while (name[0] != EOF && info[0] != (unsigned long)EOF && info[1] != (unsigned long)EOF) {
		if(scanf("%s%ld%ld", name, &info[0], &info[1]) != EOF) {
			break;
		}
		else {
			printf("%s\t\t%6ld\t%6ld", name, info[0], info[1]);
		}
	}
	fclose(fp);
	Input();
	return;
}
