#include "../include/head.h"

void Settings() {
	unsigned short where = 1, a = 0;  //对应的位置
	unsigned short esc = 0;
	int inputContent = 0;    //输入
	struct winsize size;
	int startSize = 0;

	printf("\033[?25h");
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	startSize = size.ws_col / 2 - 25;
	/* 打印菜单 */
	while (inputContent != 'q' && inputContent != 'Q' && inputContent != 0x1B) {
		Clear2
		/* 显示菜单 */
		Menu2("游戏设置", 1, 1);
		printf("\033[0;1;33m\033[3;%dHq键保存并退出\033[0m\033[8;%dH延迟秒数：%ld\033[8;%dH延迟微秒数：%ld", startSize, startSize, tick.it_interval.tv_sec, startSize + 32, tick.it_interval.tv_usec);
		kbhitGetchar();
		if (where % 2) {
			printf("\033[%d;%dH", (where + 1) / 2 + 7, startSize + 10 + (where + 1) % 2 * 32);
		}
		else {
			printf("\033[%d;%dH", where / 2 + 7, startSize + 10 + (where + 1) % 2 * 32);
		}
		inputContent = getch();
		/* 更改状态 */
		if (inputContent == 0x1B) {
			if (kbhit() == 1) {
				kbhitGetchar();
				inputContent = getchar();
				esc = 1;
			}
			else {
				esc = 0;
			}
		}
		if (((esc && inputContent == 'D') || (!esc && (inputContent == 'a' || inputContent == 'A'))) && where > 1) {
			where--; /* 左 */
		}
		else if (((esc && inputContent == 'C') || (!esc && (inputContent == 'd' || inputContent == 'D'))) && where < 2) {
			where++; /* 右 */
		}
		//  else if (((esc && inputContent == 'A') || (!esc && (inputContent == 'w' || inputContent == 'W'))) && where > 2) {
		//          where -= 2; /* 上 */
		//  }
		//  else if (((esc && inputContent == 'B') || (!esc && (inputContent == 's' || inputContent == 'S'))) && where < 3) {
		//          where += 2; /* 下 */
		//          if (where == 4) {
		//                  where = 3;
		//          }
		//  }
		else if ((inputContent == '+' || inputContent == '=') && where == 1) {
			tick.it_interval.tv_sec++;
		}
		else if (inputContent == '-' && where == 1) {
			tick.it_interval.tv_sec--;
		}
		else if ((inputContent == '+' || inputContent == '=') && where == 2) {
			tick.it_interval.tv_usec += 1000;
		}
		else if (inputContent == '-' && where == 2) {
			tick.it_interval.tv_usec -= 1000;
		}
	}
	printf("\033[?25l");
	return;
}

