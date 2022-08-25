#include "../include/head.h"

struct itimerval tick;

int main()
{
	int inputContent = 1;

	menuData menu = menuDataInit(), help = menuDataInit();

	menu.title = "贪吃蛇游戏";
	menu.addText(&menu, "1.开始游戏", "2.游戏帮助",
		     "3.游戏设置", NULL);
	menu.addTextData(&menu, 0, "%s%s%s", "%z开始贪吃蛇游戏%z",
			 "%z查看游戏的全部帮助%z",
			 "%z设置游戏的更新时间（更新间隔），分别为秒与微秒。延迟数字越大游戏速度越慢%z");

	help.title = "游戏帮助";
	help.cfg = 2;
	help.addText(&help,
		     "1.%z主界面可以使用%zWASD%z或者方向键再或%zvim%z键位移动选择的选项，并且按下空格或回车选择对应的选项光标移动到当页尽头后如果还有内容会翻页到下一页，右下角会有当前所在的页数和总页数的提示%z",
		     "2.%z游戏界面可以使用同主界面一样的键位移动方向%z",
		     "3.%z在游戏中可以使用%zq%z退出，或者使用%zp%z来暂停。%z",
		     "4.%z游戏帮助按下除了移动光标外按键的其他按键应该会退出帮助界面",
		     NULL);

	/* 定时间隔 */
	tick.it_interval.tv_sec = 0;
	tick.it_interval.tv_usec = 90000;
	/* 延迟启动 */
	tick.it_value.tv_sec = 0;
	tick.it_value.tv_usec = 100000;

	signal(SIGINT, stop);

	while (inputContent != 0x1B && inputContent != '0'
	       && inputContent != 'Q' && inputContent != 'q') {
		clear();
		inputContent = menu.menuShow(&menu);
		switch (inputContent) {
		case '1':
			Game();
			break;
		case '2':
			help.menuShow(&help);
			break;
		case '3':
			Settings();
			break;
		default:
			break;
		}
	}
	endwin();
	return 0;
}

void stop()
{
	alarm(0);
	endwin();
	printf("退出......");
	exit(0);
}
