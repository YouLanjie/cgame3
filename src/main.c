#include "../include/head.h"

struct itimerval tick;

extern ctools_menu CT_MENU;

int main()
{
	int inputContent = 1;
	ctools_menu *m = &CT_MENU;
	struct ctools_menu_t * menu = NULL,
		             * help = NULL;

	m->ncurses_init();

	init_pair(1, COLOR_WHITE, COLOR_BLUE);      /* 蓝底白字 */

	m->data_init(&menu);
	m->data_init(&help);
	m->set_title(menu, "贪吃蛇游戏");
	m->add_text(menu,
			"1.开始游戏",
			"2.游戏帮助",
			"3.游戏设置",
			NULL);
	m->add_text_data(menu, "describe", "%s%s%s",
			"开始贪吃蛇游戏",
			"查看游戏的全部帮助",
			"设置游戏的更新时间（更新间隔），分别为秒与微秒。延迟数字越大游戏速度越慢");

	m->set_title(help, "游戏帮助");
	m->set_type(help, "help");
	m->add_text(help,
		     "1.主界面可以使用WASD或者方向键再或vim键位移动选择的选项，并且按下空格或回车选择对应的选项光标移动到当页尽头后如果还有内容会翻页到下一页，右下角会有当前所在的页数和总页数的提示",
		     "2.游戏界面可以使用同主界面一样的键位移动方向",
		     "3.在游戏中可以使用q退出，或者使用p来暂停。",
		     "4.游戏帮助按下除了移动光标外按键的其他按键应该会退出帮助界面",
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
		inputContent = m->show(menu);
		switch (inputContent) {
		case '1':
			Game();
			break;
		case '2':
			m->show(help);
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
