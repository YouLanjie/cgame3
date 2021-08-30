#include "../include/head.h"

void Top() {
	struct winsize size;
	unsigned int info[2] = {0, 0};
	FILE * fp;

	KbhitNoTime();
	Clear2
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	fp = fopen("top.txt","r");
	if (!fp) {
		printf("存档不存在");
		Input();
		return;
	}
	printf("\033[2;%dH\033[1;32m排行榜\n", size.ws_col / 2 - 3);
	printf("\033[1;32m\033[4;%dH|\033[1;33m长  度      分  数\033[32m|\033[0m\n", size.ws_col / 2 - 10);
	while (info[0] != (unsigned)EOF && info[1] != (unsigned)EOF) {
		if(fscanf(fp,"%d%d", &info[0], &info[1]) == EOF) {
			break;
		}
		else {
			printf("\033[%dC\033[1;32m|\033[1;33m%6d        %4d\033[1;32m|\033[0m\n", size.ws_col / 2 - 11, info[0], info[1]);
			KbhitNoTime();
		}
	}
	fclose(fp);
	Input();
	return;
}
