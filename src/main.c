#include "../include/head.h"

struct itimerval tick;

int main() {
	int inputContent = 1;

	menuData menu = menuDataInit(), help = menuDataInit();

	menu.title = "贪吃蛇游戏";
	menu.addText(&menu, "1.开始游戏", "2.历史记录", "3.游戏帮助", "4.清除记录", "5.游戏设置", NULL);
	menu.addTextData(&menu, 0, "%s%s%s%s%s", "%z开始贪吃蛇游戏%z", "%z查看保存着的全部的历史记录%z，%z使用文本形式%z(txt)%z储存%z", "%z查看游戏的全部帮助%z", "%z这会删除记录文件并且没有任何的提示%z，%z请不要轻易这么做%z", "%z设置游戏的更新时间（更新间隔），分别为秒与微秒。延迟数字越大游戏速度越慢%z");

	help.title = "游戏帮助";
	help.cfg   = 2;
	help.addText(&help, "1.%z主界面可以使用%zWASD%z或者方向键再或%zvim%z键位移动选择的选项，并且按下空格或回车选择对应的选项光标移动到当页尽头后如果还有内容会翻页到下一页，右下角会有当前所在的页数和总页数的提示%z", "2.%z游戏界面可以使用同主界面一样的键位移动方向%z", "3.%z在游戏中可以使用%zq%z退出，或者使用%zp%z来暂停。%z", "4.%z历史记录只是简单地储存蛇的长度与对应的分数，没有什么特别的，不喜可删%z", "6.%z清除记录选项会直接移除保存游戏记录的所有文件这没有什么可怕的，毕竟文件的所有的内容都是明文记录的（长度%z+%z分数），而且历史记录能够保存的内容都是极其有限的，功能也很简陋%z", "5.%z游戏帮助按下除了移动光标外按键的其他按键应该会退出帮助界面", NULL);

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
		inputContent = menu.menuShow(&menu);
		Clear
		switch (inputContent) {
			case '1':
				Game();
				break;
			case '2':
				history();
				break;
			case '3':
				help.menuShow(&help);
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

