#include "include.h"
#include <stdio.h>
#include <sys/types.h>

// ======================================================================================================================================================
// ======================================================================== 通用 ========================================================================
// ======================================================================================================================================================


// ======================================================================== Linux =======================================================================
// ======================================================================================================================================================
//
#ifdef __linux
	#include <termios.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <asm-generic/ioctls.h>

#ifndef fontColorSet
	#define fontColorSet(a,b) printf("\033[%d;%dm",a, b)
#endif
#ifndef gotoxy
	#define gotoxy(x,y) printf("\033[%d;%dH",x, y)
#endif

	/* 判断有没有输入 */
	extern int kbhit() {
		struct termios oldt, newt;
		int ch;
		int oldf;
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);
		if(ch != EOF) {
			ungetc(ch, stdin);
			return 1;
		}
		return 0;
	}

	/* 不循环输入 */
	extern int kbhitGetchar() {
		struct termios oldt, newt;
		int ch;
		int oldf;
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);
		if(ch != EOF) {
			ungetc(ch, stdin);
			return ch;
		}
		return 0;
	}

	extern int getch() {
		struct termios tm, tm_old;
		int fd = 0, ch;
	 
		if (tcgetattr(fd, &tm) < 0) {                   //保存现在的终端设置
			return -1;
		}
		tm_old = tm;
		cfmakeraw(&tm);                                 //更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
		if (tcsetattr(fd, TCSANOW, &tm) < 0) {          //设置上更改之后的设置
			return -1;
		}
		ch = getchar();
		if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {      //更改设置为最初的样子
			return -1;
		}
		return ch;
	}
	void Menu2(char title[], short pages, short allPages) {   /* 菜单#1带翻页提示的菜单 */
		struct winsize size;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		int winSizeCol = size.ws_col;

		printf("\033[0;2;32m\033[6;%dH↑\033[10;%dH↓\033[11;%dH\033[2;32m%d/%d\033[1;33m", winSizeCol / 2 - 1, winSizeCol / 2 - 1, winSizeCol / 2 + 25, pages,allPages);
		printf("\033[2;%dH\033[0;1;32m%s", winSizeCol / 2 - (int)strlen(title) / 2, title);
		printf("\033[5;%dH\033[34m--------------------------------------------------------", winSizeCol / 2 - 27);
		for (int i = 0; i < 7; i++) {
			gotoxy(i + 6, winSizeCol / 2 - 27);
			printf("|\033[54C|");
		}
		printf("\033[13;%dH--------------------------------------------------------", winSizeCol / 2 - 27);
		printf("\033[11;%dH\033[1;31m请选择:\033[0m", winSizeCol / 2 - 23);
		return;
	}
	void Menu3(char title[]) {  /* 菜单#2纯洁 */
			struct winsize size;
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
			int winSizeCol = size.ws_col;

			printf("\033[2;%dH\033[0;1;32m%s", winSizeCol / 2 - (int)strlen(title) / 2, title);
			printf("\033[5;%dH\033[0;2;34m--------------------------------------------------------", winSizeCol / 2 - 27);
			for (int i = 0; i < 7; i++) {
				gotoxy(i + 6, winSizeCol / 2 - 27);
				printf("|\033[54C|");
			}
			printf("\033[13;%dH--------------------------------------------------------", winSizeCol / 2 - 27);
			printf("\033[11;%dH\033[1;31m按任意按键返回：\033[0m", winSizeCol / 2 - 23);
		return;
	}
#endif

// ======================================================================================================================================================
// ========================================================================= End ========================================================================


// ======================================================================== Windows =====================================================================
// ======================================================================================================================================================
#ifdef _WIN32
	#include <windows.h>
	#include <conio.h>

	void gotoxy(int x,int y) { //光标定位函数
		COORD p;//定义结构体变量p
		HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前函数句柄
		p.X = y;
		p.Y = x;   //将光标的目标移动位置传递给结构体
		SetConsoleCursorPosition(handle,p);//移动光标
	}
	int kbhitGetchar() {
		if (kbhit()) {
			return getch();
		}
		else {
			return 0;
		}
	}
	void Menu2(char title[], short pages, short allPages) {
		int winSizeCol = 56;

		gotoxy(6, winSizeCol / 2 - 1);
		printf("↑");
		gotoxy(10, winSizeCol / 2 - 1);
		printf("↓");
		gotoxy(11, winSizeCol / 2 + 24);
		printf("%d/%d", pages,allPages);
		gotoxy(2, winSizeCol / 2 - (int)strlen(title) / 2);
		printf("%s", title);
		gotoxy(5, winSizeCol / 2 - 27);
		printf("--------------------------------------------------------");
		for (int i = 0; i < 7; i++) {
			gotoxy(i + 6, winSizeCol / 2 - 27);
			printf("|");
			gotoxy(i + 6, winSizeCol / 2 + 27);
			printf("|");
		}
		gotoxy(13, winSizeCol / 2 - 27);
		printf("--------------------------------------------------------");
		gotoxy(11, winSizeCol / 2 - 23);
		printf("请选择:");
	}
	void Menu3(char title[]) {
		int winSizeCol = 56;

		gotoxy(2, winSizeCol / 2 - (int)strlen(title) / 2);
		printf("%s", title);
		gotoxy(5, winSizeCol / 2 - 27);
		printf("--------------------------------------------------------");
		for (int i = 0; i < 7; i++) {
			gotoxy(0, 0);
			gotoxy(i + 6, winSizeCol / 2 - 27);
			printf("|");
			gotoxy(i + 6, winSizeCol / 2 + 27);
			printf("|");
		}
		gotoxy(13, winSizeCol / 2 - 27);
		printf("--------------------------------------------------------");
		gotoxy(11, winSizeCol / 2 - 23);
		printf("按任意按键返回：");
	}
#endif

// ======================================================================================================================================================
// ======================================================================== End =========================================================================


// ======================================================================== Def =========================================================================
// ======================================================================================================================================================

#ifdef __linux
	#ifndef Clear
		#define Clear printf("\033[2J\033[1;1H");
	#endif
	#ifndef Clear2
		#define Clear2 system("clear");
	#endif
#endif
#ifdef _WIN32
	#ifndef Clear
		#define Clear gotoxy(0, 0); for (int i = 0;i < 50; i++) { printf("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    "); } gotoxy(0, 0);
		#define Clear2 gotoxy(0, 0); for (int i = 0;i < 50; i++) { printf("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    "); } gotoxy(0, 0);
	#endif
#endif

// ======================================================================================================================================================
// ======================================================================== End =========================================================================


// ======================================================================= Menu =========================================================================
// ======================================================================================================================================================

int Menu(char *title, char *text[], int tl, int list) { /* 菜单程序 */
#ifdef __linux
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int winSizeCol = size.ws_col;
#else
	int winSizeCol = 56;
#endif
	int input = 1, currentPage = 1, count = 1, allPages = (tl - 1) / (4 * list) + 1;

	if (list <= 0 || list > 2) {
		list = 2;
	}

	while (input != 0x30 && input != 0x1B) {
		Clear2
#ifdef __linux
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		winSizeCol = size.ws_col;
#endif

#ifdef __linux
		printf("\033[5;%dH\033[0;2;34m--------------------------------------------------------", winSizeCol / 2 - 27);
		for (int i = 0; i < 7; i++) {
			gotoxy(i + 6, winSizeCol / 2 - 27);
			printf("\033[0;2;34m|\033[54C|");
		}
		printf("\033[13;%dH--------------------------------------------------------", winSizeCol / 2 - 27);
		printf("\033[0;2;32m\033[6;%dH↑\033[11;%dH↓\033[11;%dH\033[0;2;32m%d/%d\033[0;1;33m", winSizeCol / 2 - 1, winSizeCol / 2 - 1, winSizeCol / 2 + 25, currentPage,allPages);
		printf("\033[2;%dH\033[1;32m%s\033[0m", winSizeCol / 2 - (int)strlen(title) / 2, title);
#else
		gotoxy(6, winSizeCol / 2 - 1);
		printf("↑");
		gotoxy(11, winSizeCol / 2 - 1);
		printf("↓");
		gotoxy(11, winSizeCol / 2 + 24);
		printf("%2d/%2d", currentPage,allPages);
		gotoxy(2, winSizeCol / 2 - (int)strlen(title) / 2);
		printf("%s", title);
		gotoxy(5, winSizeCol / 2 - 27);
		printf("--------------------------------------------------------");
		for (int i = 0; i < 7; i++) {
			gotoxy(i + 6, winSizeCol / 2 - 27);
			printf("|");
			gotoxy(i + 6, winSizeCol / 2 + 27);
			printf("|");
		}
		gotoxy(13, winSizeCol / 2 - 27);
		printf("--------------------------------------------------------");
#endif
		for (int i = 1; i <= tl - list * 4 * (currentPage - 1) && i <= list * 4; i++) {
			if (i != count) {
#ifdef __linux
				printf("\033[33m\033[%d;%dH%s\033[0m", (i + 1) / list + 6 - list % 2, winSizeCol / 2 - 20 + ((i + 1) % list) * 32, text[i - 1 +  list * 4 * (currentPage - 1)]);
#else
				gotoxy((i + 1) / list + 6 - list % 2, winSizeCol / 2 - 20 + ((i + 1) % list) * 32);
				printf("%s", text[i - 1 +  list * 4 * (currentPage - 1)]);
#endif
			}
			else {
#ifdef __linux
				printf("\033[1;7;33m\033[%d;%dH%s\033[0m", (i + 1) / list + 6 - list % 2, winSizeCol / 2 - 20 + ((i + 1) % list) * 32, text[i - 1 +  list * 4 * (currentPage - 1)]);
#else
				gotoxy((i + 1) / list + 6 - list % 2, winSizeCol / 2 - 20 + ((i + 1) % list) * 32 - list);
				printf("> %s", text[i - 1 +  list * 4 * (currentPage - 1)]);
#endif
			}
			kbhitGetchar();
		}
		input = getch();
		if (input == 0x1B) {
			if (kbhit()) {
				getchar();
				input = getchar();
				if (input == 'A') {
					if (count > list) {
						count -= list;
					}
					else if (currentPage > 1){
						count += list * 3;
						currentPage--;
					}
				}
				else if (input == 'B') {
					if (count < list * 4 - (list + 1) % 2 && count + list * 4 * (currentPage - 1) <= tl - list) {
						count += list;
					}
					else if (currentPage < allPages){
						count -= list * 3;
						currentPage++;
						if (count + (4 * list) * (currentPage - 1) > tl) {
							count -= 1;
						}
					}
				}
				else if (input == 'C') {
					if (count < list * 4 && count + list * 4 * (currentPage - 1) < tl) {
						count++;
					}
					else if (currentPage < allPages){
						count = 1;
						currentPage++;
					}
				}
				else if (input == 'D') {
					if (count > 1) {
						count--;
					}
					else if (currentPage > 1){
						count = list * 4;
						currentPage--;
					}
				}
			}
			else {
				Clear2
				return 0;
			}
		}
		else if (input == 'w' || input == 'W' || input == 'k' || input == 'K') {
			if (count > list) {
				count -= list;
			}
			else if (currentPage > 1){
				count += list * 3;
				currentPage--;
			}
		}
		else if (input == 's' || input == 'S' || input == 'j' || input == 'J') {
			if (count < list * 4 - (list + 1) % 2 && count + list * 4 * (currentPage - 1) <= tl - list) {
				count += list;
			}
			else if (currentPage < allPages){
				count -= list * 3;
				currentPage++;
				if (count + (4 * list) * (currentPage - 1) > tl) {
					count -= 1;
				}
			}
		}
		else if (input == 'd' || input == 'D' || input == 'l' || input == 'L') {
			if (count < list * 4 && count + list * 4 * (currentPage - 1) < tl) {
				count++;
			}
			else if (currentPage < allPages){
				count = 1;
				currentPage++;
			}
		}
		else if (input == 'a' || input == 'A' || input == 'h' || input == 'H') {
			if (count > 1) {
				count--;
			}
			else if (currentPage > 1){
				count = list * 4;
				currentPage--;
			}
		}
		else if (input == 'q' || input == 'Q') {
			Clear
			return '0';
		}
		else if (input == ' ' || input == '\r' || input == '\n') {
			Clear2
			char output[10];
			sprintf(output, "%d", count + 8 * (currentPage - 1));
			return output[0];
		}
		else {
			Clear2
			return input;
		}
	}
	return 0;
}

// ======================================================================================================================================================
// ======================================================================== End =========================================================================


// ====================================================================== NewMenu =======================================================================
// ======================================================================================================================================================

// 定义数据类型
// ======================================================================================================================================================

//  struct Text {
//          char        * text;         /* 条例内容 */
//          char        * describe;     /* 描述/帮助信息 */
//          void       (* function);    /* 调用的函数 */
//          int           number;       /* 编号 */
//          int           cfg;          /* 类型 */
//          struct Text * nextText;     /* 下一条例（链表） */
//  };                                  /* 条例结构体 */
//
//  typedef struct _menuData{
//          char        * title;                                                                      /* 标题 */
//          struct Text * text;                                                                       /* 条例链表头 */
//          struct Text * focus;                                                                      /* 选中的条例 */
//          int           cfg;                                                                        /* 菜单状态 */
//          void       (* addText)    (struct _menuData * data, ...);                                 /* 添加条例 */
//          void       (* addTextData)(struct _menuData * data, int type, char * format, ...);       /* 添加条例信息 */
//          void       (* getFocus)   (struct _menuData * data, int number);                          /* 更改焦点指针 */
//  }menuData;                                                                                        /* 菜单类/结构体 */

// 函数声明
// ======================================================================================================================================================

//  void menuDataInit(menuData * data);
//  void _menuAddText(menuData * data, ...);
//  void _menuAddTextData(menuData * data, int type, char * format, ...);
//  void _menuGetFocus(menuData * data, int number);
//  static void MenuScreen();

//
// ======================================================================================================================================================

#define LineH "─"
#define LineV "│"
#define LineLU "┌"
#define LineLD "└"
#define LineRU "┐"
#define LineRD "┘"
#define LineLC "├"
#define LineRC "┤"
#define LineCC "┼"
#define LineUC "┬"
#define LineDC "┴"
#define LineCLU "╭"
#define LineCLD "╰"
#define LineCRU "╮"
#define LineCRD "╯"
#define ArrowOn "↑"
#define ArrowDn "↓"
#define ArrowLf "←"
#define ArrowRi "→"

void menuDataInit(menuData * data) {    /* 初始化结构体 */
	data -> title       = NULL;
	data -> text        = NULL;
	data -> focus       = NULL;
	data -> cfg         = 0;
	data -> addText     = _menuAddText;
	data -> addTextData = _menuAddTextData;
	data -> getFocus    = _menuGetFocus;
	data -> menuShow    = _menu;
	return;
}

void _menuAddText(menuData * data, ...) {
	struct Text * pNew, * pTmp;
	va_list text;

	va_start(text, data);
	if (data -> text != NULL) {
		free(data -> text);
	}

	pNew = data -> text = malloc(sizeof(struct Text));
	pNew -> text     = va_arg(text, char *);
	pNew -> number   = 1;
	pNew -> describe = NULL;
	pNew -> cfg      = 0;

	for (int i = 2; pNew -> text != NULL; i++) {
		pTmp             = pNew;
		pNew -> nextText = malloc(sizeof(struct Text));
		pNew             = pNew -> nextText;
		pNew -> text     = va_arg(text, char *);
		pNew -> describe = NULL;
		pNew -> number   = i;
		pNew -> cfg      = 0;
	}
	free(pNew);
	pTmp -> nextText = NULL;
	va_end(text);
	return;
}

void _menuAddTextData(menuData * data, int type, char * format, ...) {    /* type:0 -> describe, 1 -> function */
	struct Text * pNew;
	va_list text;

	va_start(text, format);
	pNew = data -> text;
	while (*format != '\0') {
		if (*format == '%' && *(format + 1) == 's') {
			if (!type) {
				pNew -> describe = va_arg(text, char *);
			}
			else {
				pNew -> function = va_arg(text, void *);
			}
			pNew = pNew -> nextText;
			format++;
		}
		else if (*format == '\n' || *format == 'n' || *format == 'N') {
			pNew = pNew -> nextText;
		}
		format++;
	}
	va_end(text);
	return;
}

void _menuGetFocus(menuData * data, int number) {
	if (data -> focus == NULL) {
		data -> focus = data -> text;
	}
	if (number <= 0) {
		while (data -> focus -> nextText != NULL) {
			data -> focus = data -> focus -> nextText;
		}
		return;
	}
	if (data -> focus -> number > number) {
		data -> focus = data -> text;
	}
	while (data -> focus -> number < number) {
		data -> focus = data -> focus -> nextText;
	}
	return;
}

// NewMenu
// ======================================================================================================================================================

#define winSizeCol size.ws_col    /* x轴 */
#define winSizeRol size.ws_row    /* y轴 */

/* 交换变量的值 */
#define Swap(a,b) \
	a = a^b;  \
	b=a^b;    \
	a=a^b;

int _menu(menuData * data) {
#ifdef __linux
	/* 定义保存窗口大小的结构体变量 */
	struct winsize size;

	/* 获取最后一条文本的信息 */
	data -> getFocus(data, 0);

	int    input       = 1,                          /* 保存输入 */
	       focus       = 1,                          /* 保存焦点选项的数字 */
	       focus2      = 0,                          /* 描述的焦点 */
	       noShowText  = 0,                          /* 显示的内容与读取的偏差值（相当于屏幕上方隐藏的条目），用作实现界面滑动 */
	       noShowText2 = 0,                          /* 偏差值的备份 */
	       allChose    = data -> focus -> number,    /* 保存所有的选择总数 */
	       allDescribe = 0;                          /* 保存所有的描述字符行总数 */

	while (input != 0x30 && input != 0x1B) {
		//铺上底色
		printf("\033[0;44;37m");
		Clear
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		winSizeCol = size.ws_col;

		/* 显示屏幕框架 */
		_menuShowScreen(data);

		/* 打印选项 */
		_menuShowText(data, focus, noShowText, allChose);

		/* 显示焦点选项的描述 */
		_menuShowDescribe(data, focus, focus2, noShowText2, &allDescribe);

		if (focus2) {
			Swap(focus, focus2);
			Swap(allChose, allDescribe);
			Swap(noShowText, noShowText2);

			/* 打印描述的按键提示 */
			printf("\033[0;1;47;30m\033[8;%dH%sw k%s\033[%d;%dH%ss j%s\033[0m", winSizeCol / 4 * 3 - 3, ArrowOn, ArrowOn, winSizeRol - 1, winSizeCol / 4 * 3 - 3, ArrowDn, ArrowDn);
			printf("\033[0;1;47;30m\033[%d;%dH%02d/%02d\033[0m", winSizeRol - 1, winSizeCol - 6, focus, allChose);
			printf("\033[0;1;44;37m\033[6;%dH%sTAB\033[0m", winSizeCol / 2 + 1, ArrowLf);
		}
		else {
			/* 打印选项的按键提示 */
			printf("\033[0;1;44;37m\033[8;%dH%sw k%s\033[%d;%dH%ss j%s\033[0m", winSizeCol / 4 - 3, ArrowOn, ArrowOn, winSizeRol - 1, winSizeCol / 4 - 3, ArrowDn, ArrowDn);
			printf("\033[0;1;44;37m\033[%d;%dH%02d/%02d\033[0m", winSizeRol - 1, winSizeCol / 2 - 5, focus, allChose);
			if (data -> focus -> describe != NULL) {
				printf("\033[0;1;44;37m\033[6;%dHTAB%s\033[0m", winSizeCol / 2 - 4, ArrowRi);
			}
		}
		input = getch();
		switch (_menuInput(&input, &focus, &noShowText, allChose)) {
			case '\n':
				Clear2
				char output[10];    /* 仅用作字符输出 */
				sprintf(output, "%d", focus);
				return output[0];
				break;
			case '0':
				Clear
				return '0';
				break;
			case 0:
				break;
			case '\t':    /* 切换介绍与选项 */
				if (data -> focus -> describe != NULL) {
					if (!focus2) {
						focus2 = focus;
						focus = 1;
						noShowText2 = noShowText;
						noShowText = 0;
						allDescribe = allChose;
					}
					else {
						Swap(focus, focus2);
						Swap(allChose, allDescribe);
						Swap(noShowText, noShowText2);
						focus2 = 0;
						noShowText2 = 0;
					}
				}
				break;
			default:
				return input;
				break;
		}
		if (focus2) {
			Swap(focus, focus2);
			Swap(allChose, allDescribe);
			Swap(noShowText, noShowText2);
		}
	}
#endif
	return 0;
}

// MenuScreen
// ======================================================================================================================================================

void _menuShowScreen(menuData * data) {
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

	//铺上底色
	printf("\033[0;44;37m");
	Clear
	printf("\033[1;1H");
	printf(LineLU);
	for (int i = 2; i < winSizeCol; i++) {
		printf("\033[1;%dH%s\033[5;%dH%s\033[%d;%dH%s\033[7;%dH%s", i, LineH, i, LineH, winSizeRol, i, LineH, i, LineH);
	}
	printf("\033[6;%dH选项\033[6;%dH描述",winSizeCol / 4 - 2, winSizeCol /4 * 3 - 2);
	for (int i = 2; i < winSizeRol; i++) {
		printf("\033[%d;1H%s\033[%d;%dH%s", i, LineV, i, winSizeCol, LineV);
		if (i >= 6) {
			printf("\033[%d;%dH%s", i, winSizeCol / 2, LineV);
		}
	}
	for (int i = 2; i < winSizeCol; i++) {
	}
	printf("\033[%d;1H%s\033[%d;%dH%s\033[1;%dH%s\033[5;1H%s\033[5;%dH%s\033[5;%dH%s\033[%d;%dH%s\033[7;%dH%s\033[7;1H%s\033[7;%dH%s", winSizeRol, LineLD, winSizeRol, winSizeCol, LineRD, winSizeCol, LineRU, LineLC, winSizeCol, LineRC, winSizeCol / 2, LineUC, winSizeRol ,winSizeCol / 2, LineDC, winSizeCol / 2, LineCC, LineLC, winSizeCol, LineRC);
	//  printf("\033[0;2;44;32m\033[6;%dH↑\033[11;%dH↓\033[11;%dH\033[0;2;44;32m%d/%d\033[0;1;44;33m", winSizeCol / 2 - 1, winSizeCol / 2 - 1, winSizeCol / 2 + 25, currentPage,allPages);
	printf("\033[3;%dH\033[1;44;37m%s\033[0m", winSizeCol / 2 - (int)strlen(data -> title) / 2, data -> title);
	
	return;
}

void _menuShowText(menuData * data, int focus, int noShowText, int allChose) {
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

	printf("\033[0;30;47m");
	for (int i = 1; i - noShowText <= allChose && i - noShowText <= winSizeRol - 10; i++) {
		if (i <= noShowText) {
			continue;
		}
		data -> getFocus(data, i);
		if (i != focus) {
			printf("\033[0;44;37m");
		}
		else {
			printf("\033[1;7;47;33m");
		}
		printf("\033[%d;4H", i + 8 - noShowText);
		for (int i = 0; i <= winSizeCol / 2 - 7; i++) {
			printf(" ");
		}
		printf("\033[%d;4H%s\033[0m", i + 8 - noShowText, data -> focus -> text);
		kbhitGetchar();
	}
	return;
}

void _menuShowDescribe(menuData * data, int focus, int focus2, int noShowText2, int * allDescribe) {
	struct winsize size;
	char * ch = NULL;    /* 用于打印描述字符时自动折行 */

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

	printf("\033[0;30;47m");
	for (int i = 8; i <= winSizeRol - 1; i++) {    /* 打底色 */
		printf("\033[%d;%dH", i, winSizeCol / 2 + 2);
		for (int i2 = winSizeCol / 2 + 2; i2 <= winSizeCol - 2; i2++) {
			printf(" ");
		}
	}

	data -> getFocus(data, focus);
	if (data -> focus -> describe != NULL) {
		int stat = 1;
		int i = 1, i2 = 9;

		printf("\033[9;%dH\033[0;30;47m", winSizeCol / 2 + 3);
		ch = data -> focus -> describe;
		for (i = 1; *ch != '\0' && i2 - 8 - noShowText2 <= winSizeRol - 10; i++) {
			if (i2 - 8 == focus2 && stat) {
				printf("\033[0;7;30;47m");
				stat = 0;
			}
			if (i2 - 9 >= noShowText2) {
				printf("%c", *ch);
			}
			else {
				printf("\033[%d%dH", i2 - noShowText2, winSizeCol / 2 +3);
			}
			ch++;
			if (i >= winSizeCol / 2 - 4 || *ch == '\n' || *ch == '\r') {
				if (i2 - 8 == focus2) {
					printf("\033[0;30;47m");
				}
				i2++;
				printf("\033[%d;%dH", i2 - noShowText2 , winSizeCol / 2 + 3);
				i = 0;
				kbhitGetchar();
				ch++;
			}
		}
		ch = data -> focus -> describe;
		*allDescribe = 1;
		i = 1;
		while (*ch != '\0') {
			if (i >= winSizeCol / 2 - 4 || *ch == '\n' || *ch == '\r') {
				(*allDescribe)++;
				i = 0;
			}
			ch++;
			i++;
		}
	}
	return;
}

int _menuInput(int * input, int * focus, int * noShowText, int allChose) {
	struct winsize size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

	switch (*input) {
		case 0x1B:
			if (kbhit() != 0) {
				getchar();
				*input = getch();
				switch (*input) {
					case 'A':
					case 'D':
						if (*focus > 1) {
							(*focus)--;
						}
						while (*focus - *noShowText < 1) {
							(*noShowText)--;
						}
						break;
					case 'B':
					case 'C':
						if (*focus < allChose) {
							(*focus)++;
						}
						while (*focus - *noShowText > winSizeRol - 10) {
							(*noShowText)++;
						}
						break;
				}
			}
			else {
				Clear2
				return '0';
			}
			break;
		case 'd':
		case 'D':
		case 'l':
		case 'L':
		case 's':
		case 'S':
		case 'j':
		case 'J':
			if (*focus < allChose) {
				(*focus)++;
			}
			while (*focus - *noShowText > winSizeRol - 10) {
				(*noShowText)++;
			}
			break;
		case 'a':
		case 'A':
		case 'h':
		case 'H':
		case 'w':
		case 'W':
		case 'k':
		case 'K':
			if (*focus > 1) {
				(*focus)--;
			}
			while (*focus - *noShowText < 1) {
				(*noShowText)--;
			}
			break;
		case 'q':
		case 'Q':
		case '0':
			Clear
			return '0';
			break;
		case ' ':
		case '\n':
		case '\r':
			return '\n';
			break;
		case '\t':
			return '\t';
			break;
	}
	Clear2
	return 0;
}

#undef Swap

#undef winSizeCol
#undef winSizeRol

#undef LineH 
#undef LineV 
#undef LineLU
#undef LineLD
#undef LineRU
#undef LineRD
#undef LineLC
#undef LineRC
#undef LineCC
#undef LineUC
#undef LineDC
#undef LineCLU
#undef LineCLD
#undef LineCRU
#undef LineCRD
#undef ArrowOn
#undef ArrowDn

