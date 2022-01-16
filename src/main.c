#include "../include/head.h"

int main() {
	int inputContent = 1;
	struct winsize size;
	int startSize = 0;

	printf("\033[?25l");
	Clear2
	signal(SIGINT,stop);
	while (inputContent != 0x1B && inputContent != 0x30 && inputContent != 0x51 && inputContent != 0x71) {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		if (size.ws_col < 56 || size.ws_row < 13) {
			Clear2
			printf("终端至少要 56 × 13 那么大，否则会出现问题\033[?25h\n");
			return 1;
		}
		startSize = size.ws_col / 2 - 20;
		printf("\033[8;%dH\033[1;33m1.开始游戏\033[8;%dH2.排行榜\033[9;%dH3.游戏帮助\033[9;%dH4.清除记录\n", startSize, startSize + 32, startSize, startSize + 32);
		Menu("游戏", 1, 1);
		inputContent = getch();
		Clear
		switch (inputContent) {
			case 0x31:
				Game();
				break;
			case 0x32:
				Top();
				break;
			case 0x33:
				printf("\033[9;%dHESC Q 0退出方向键移动\n", startSize + 10);
				Menu2("帮助");
				getch();
				break;
			case 0x34:
				remove("top.txt");
				break;
			default:
				break;
		}
		Clear
	}
	Clear2
	printf("\033[?25h");
	return 0;
}

void stop() {
	Clear2
	printf("\033[?25h退出......");
	exit(0);
}
