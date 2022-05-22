#include "../include/head.h"

int main() {
	int inputContent = 1;
	struct winsize size;
	int startSize = 0;
	char *text[] = {
		"1.开始游戏",
		"2.排行榜",
		"3.游戏帮助",
		"4.清除记录",
	};

	printf("\033[?25l");
	Clear2
	signal(SIGINT,stop);
	while (inputContent != 0x1B && inputContent != '0' && inputContent != 'Q' && inputContent != 'q') {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		if (size.ws_col < 56 || size.ws_row < 13) {
			Clear2
			printf("终端至少要 56 × 13 那么大，否则会出现问题\033[?25h\n");
			return 1;
		}
		startSize = size.ws_col / 2 - 20;
		inputContent = Menu("游戏", text, 4, 2);
		Clear
		switch (inputContent) {
			case '1':
				Game();
				break;
			case '2':
				Top();
				break;
			case '3':
				printf("\033[9;%dHESC Q 0退出方向键移动\n", startSize + 10);
				Menu3("帮助");
				getch();
				break;
			case '4':
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
