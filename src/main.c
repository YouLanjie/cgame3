#include "../include/head.h"

struct itimerval tick;

int main() {
	int inputContent = 1;
	struct winsize size;
	int startSize = 0;
	char *text[] = {
		"1.开始游戏",
		"2.历史记录",
		"3.游戏帮助",
		"4.清除记录",
		"5.游戏设置"
	};
	char *help[] = {
		"1.主界面可以使用WASD或者方向键再或vim键位移动",
		"  选择的选项，并且按下空格或回车选择对应的选项",
		"  光标移动到当页尽头后如果还有内容会翻页到下一",
		"  页，右下角会有当前所在的页数和总页数的提示",
		"2.游戏界面可以使用同主界面一样的键位移动方向",
		"3.在游戏中可以使用q退出，或者使用p来暂停。",
		"4.历史记录只是简单地储存蛇的长度与对应的分数，",
		"  没有什么特别的，不喜可删",
		"6.清除记录选项会直接移除保存游戏记录的所有文件",
		"  这没有什么可怕的，毕竟文件的所有的内容都是明",
		"  文记录的（长度+分数），而且历史记录能够保存",
		"  的内容都是极其有限的，功能也很简陋",
		"5.游戏帮助按下除了移动光标外按键的其他按键应",
		"  该会退出帮助界面"
	};

	/* 定时间隔 */
	tick.it_interval.tv_sec = 0;
	tick.it_interval.tv_usec = 90000;
	/* 延迟启动 */
	tick.it_value.tv_sec = 0;
	tick.it_value.tv_usec = 100000;
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
		inputContent = Menu("游戏", text, 5, 2);
		Clear
		switch (inputContent) {
			case '1':
				Game();
				break;
			case '2':
				history();
				break;
			case '3':
				Menu("帮助", help, 14, 1);
				break;
			case '4':
				remove("cgame3_save");
				break;
			case '5':
				Settings();
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
	alarm(0);
	Clear2
	printf("\033[?25h退出......");
	exit(0);
}

