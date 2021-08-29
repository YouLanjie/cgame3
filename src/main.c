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
		startSize = size.ws_col / 2 - 20;
		printf("\033[8;%dH\033[1;33m1.开始游戏\033[8;%dH2.排行榜\033[9;%dH3.游戏帮助\n", startSize, startSize + 32, startSize);
		Menu("游戏", 1, 1);
		inputContent = Input();
		Clear2
		switch (inputContent) {
			case 0x31:
				Game();
				break;
			case 0x32:
				Top();
				break;
			case 0x33:
				printf("\033[9;%dH帮助就是没有帮助\n", startSize + 12);
				Menu2("帮助");
				Input();
				break;
			default:
				break;
		}
		Clear2
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
