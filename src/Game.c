#include "../include/head.h"

extern ctools_menu CT_MENU;

static struct Snake *init();
static struct Snake *mkFood();
static void printSnake();
static void runGame();

static int way = Up;
static int Long = 0;		/* 蛇身的长度 */
static short Lock = 0;
static struct Snake *pHead = NULL, *pFood = NULL;
static struct winsize size;	/* 记录窗口大小 */

void Game()
{				/* 实现游戏的函数 */
	ctools_menu *m = &CT_MENU;
	struct ctools_menu_t *end;
	m->data_init(&end);
	m->set_title(end, "游戏结束");
	m->set_type(end, "help_only");

	way = Up;
	pHead = pFood = NULL;
	pHead = init();
	alarm(0);
	signal(SIGALRM, runGame);
	if (setitimer(ITIMER_REAL, &tick, NULL)) {
		perror("Error");
		getch();
		return;
	}
	while (way != 'q' && way != 'Q' && way != 0x1B) {
		switch (getch()) {
		case 0x1B:
			if (ctools_kbhit() != 0) {
				getchar();
				switch (getchar()) {
				case 'A':
					if (way != Down && !Lock) {
						way = Up;
					}
					break;
				case 'B':
					if (way != Up && !Lock) {
						way = Down;
					}
					break;
				case 'C':
					if (way != Left && !Lock) {
						way = Right;
					}
					break;
				case 'D':
					if (way != Right && !Lock) {
						way = Left;
					}
					break;
				}
			} else {
				way = 'q';
			}
			break;
		case 'w':
		case 'W':
		case 'k':
		case 'K':
			if (way != Down && !Lock) {
				way = Up;
			}
			break;
		case 's':
		case 'S':
		case 'j':
		case 'J':
			if (way != Up && !Lock) {
				way = Down;
			}
			break;
		case 'd':
		case 'D':
		case 'l':
		case 'L':
			if (way != Left && !Lock) {
				way = Right;
			}
			break;
		case 'a':
		case 'A':
		case 'h':
		case 'H':
			if (way != Right && !Lock) {
				way = Left;
			}
			break;
		case 'p':	/* 暂停 */
		case 'P':
			if (Lock == 1 && pHead != NULL) {	/* 如果已经暂停 */
				if (setitimer(ITIMER_REAL, &tick, NULL)) {
					perror("Error");
					getch();
					return;
				}
			} else if (Lock != 2) {	/* 如果未暂停 */
				alarm(0);
			}
			break;
		case 'o':
		case 'O':
			if (Lock == 2) {
				break;
			}
			if (!Lock && pHead != NULL) {	/* 未暂停则暂停后启用 */
				alarm(0);
			}
			Settings();
			printSnake();
			break;
		case 'q':
		case 'Q':
		case '0':
			alarm(0);
			if (pHead != NULL) {
				m->add_text(end, "结束理由：",
					    "手动退出",
					    "按Q或者Esc返回：",
					    NULL);
				m->show(end);
				refresh();
				free(pHead);
				while (1) {
					switch (getch()) {
					case 'q':
					case 'Q':
					case 0x1B:
					case '0':
						break;
					default:
						continue;
						break;
					}
					break;
				}
			}
			way = 'q';
			break;
		case '\r':
			if (pHead == NULL) {
				way = 'q';
			}
			break;
		}
		Lock = 1;
	}
	alarm(0);
	return;
}

static struct Snake *init(void)
{
	struct Snake *pNew = NULL, *pLast = NULL;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	/* 创建蛇 */
	pHead = pNew = (struct Snake *)malloc(sizeof(struct Snake));
	pHead->x = size.ws_col / 2;	/* 设置位置 */
	pHead->y = size.ws_row / 2;
	for (Long = 1; Long < 4; Long++) {
		pLast = pNew;
		pNew = (struct Snake *)malloc(sizeof(struct Snake));
		pNew->x = size.ws_col / 2;	/* 设置位置 */
		pNew->y = size.ws_row / 2 + Long;
		pNew->pNext = NULL;
		pLast->pNext = pNew;
	}
	/* 创建食物 */
	pNew->pNext = pFood = mkFood();
	/* 打印信息 */
	printSnake();
	return pHead;
}

static struct Snake *mkFood(void)
{
	struct Snake *pFood = NULL, *pNext = NULL;
	struct timeval gettime;
	short BORE = 1;

	pFood = (struct Snake *)malloc(sizeof(struct Snake));
	while (BORE) {
		gettimeofday(&gettime, NULL);
		srand(gettime.tv_usec + time(NULL));	/* 获得随机数种子 */
		pFood->x = rand() % (size.ws_col - 12) + 6;
		pFood->y = rand() % (size.ws_row - 12) + 6;
		pNext = pHead;
		while (pNext->pNext != NULL) {
			if (pFood->x == pNext->x && pFood->y == pNext->y) {
				BORE = 1;
				break;
			} else {
				BORE = 0;
			}
			pNext = pNext->pNext;
		}
	}
	return pFood;
}

static void printSnake(void)
{
	struct Snake *pNext = pHead;

	move(0, 0);
	attron(COLOR_PAIR(1));
	for (int i = 0; i < LINES; i++) {
		for (int i2 = 0; i2 < COLS; i2++) {
			printw(" ");
		}
	}

	/* 打印边框 */
	move(0, 0);
	printw(LineLU);
	for (int i = 1; i < COLS; i++) {
		mvaddstr(0, i, LineH);	/* 第一横线 */
		mvaddstr(LINES - 2, i, LineH);	/* 第三横线 */
	}
	for (int i = 1; i < LINES - 1; i++) {
		mvaddstr(i, 0, LineV);	/* 左垂线 */
		mvaddstr(i, COLS - 1, LineV);	/* 右垂线 */
	}
	mvaddstr(LINES - 2, 0, LineLD);	/*   左下角   */
	mvaddstr(LINES - 2, COLS - 1, LineRD);	/*   右下角   */
	mvaddstr(0, COLS - 1, LineRU);	/*   右上角   */

	/* 打印信息 */
	move(LINES - 1, 0);
	printw("长度:%4d", Long);
	move(LINES - 1, (COLS / 6) * 1);
	printw("分数:%4d", (Long - 4) * 10);
	move(LINES - 1, (COLS / 6) * 2);
	printw("延迟秒数:%4ld", tick.it_interval.tv_sec);
	move(LINES - 1, (COLS / 6) * 3);
	printw("延迟微秒数:%4ld", tick.it_interval.tv_usec);

	/* 打印头 */
	mvaddch(pNext->y - 1, pNext->x - 1, '@');

	/* 打印蛇身 */
	pNext = pNext->pNext;
	for (int i = 1; i < Long; i++) {
		mvaddch(pNext->y - 1, pNext->x - 1, '#');
		if (i + 1 < Long) {
			pNext = pNext->pNext;
		}
	}

	/* 打印食物 */
	mvaddch(pNext->pNext->y - 1, pNext->pNext->x - 1, '%');
	attroff(COLOR_PAIR(1));
	refresh();
	return;
}

static void runGame(void)
{
	int    tmp_x = 0,
	       tmp_y = 0;
	short  BORE = 1;    /* 循环判断 */
	struct Snake  * pLast = pHead,
		      * pNext = pHead;
	ctools_menu *m = &CT_MENU;
	struct ctools_menu_t * end = NULL;

	m->data_init(&end);
	m->set_title(end, "游戏结束");
	m->set_type(end, "help_only");

	pNext = pNext->pNext;
	while (pNext->pNext != pFood) {
		pNext = pNext->pNext;
		pLast = pLast->pNext;
	}
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	while (BORE) {
		BORE = 0;
		tmp_x = pNext->x;
		tmp_y = pNext->y;
		switch (way) {
		case Up:
			pNext->x = pHead->x;
			pNext->y = pHead->y - 1;
			break;
		case Down:
			pNext->x = pHead->x;
			pNext->y = pHead->y + 1;
			break;
		case Right:
			pNext->x = pHead->x + 1;
			pNext->y = pHead->y;
			break;
		case Left:
			pNext->x = pHead->x - 1;
			pNext->y = pHead->y;
			break;
		case 'q':
		case 'Q':
			alarm(0);
			free(pHead);
			pHead = NULL;
			break;
		}
		pNext->pNext = pHead;
		pHead = pNext;
		pLast->pNext = pFood;
		/* 死亡判定 */
		if (pHead->x <= 1 || pHead->x > size.ws_col - 1 || pHead->y <= 1
		    || pHead->y > size.ws_row - 2) {
			Lock = 2;
			alarm(0);
			clear();
			m->add_text(end, "结束理由：",
				    "让你好好走路你偏不好好走，现在撞墙了吧",
				    "按Q或者Esc返回：", NULL);
			m->show(end);
			refresh();
			free(pHead);
			pHead = NULL;
			return;
		}
		/* 死亡判定 + 食物判定 */
		BORE = 0;
		pLast = pHead;
		pNext = pHead->pNext;
		while (pNext->pNext != pFood) {
			if (pHead->x == pNext->x && pHead->y == pNext->y) {
				Lock = 2;
				alarm(0);
				clear();
				m->add_text(end, "结束理由：",
					    "吃错东西了，自己吃自己，自相残杀",
					    "按Q或者Esc返回：",
					    NULL);
				m->show(end);
				refresh();
				free(pHead);
				pHead = NULL;
				return;
			} else if (pHead->x == pFood->x && pHead->y == pFood->y) {
				BORE = 1;
			}
			pNext = pNext->pNext;
			pLast = pLast->pNext;
		}
		if (BORE) {
			/* 为蛇添加长度 */
			pFood->pNext = NULL;
			pFood->x = tmp_x;
			pFood->y = tmp_y;
			pNext->pNext = pFood;
			pLast = pNext;
			pNext = pNext->pNext;
			pFood = NULL;
			Long++;
			BORE = 0;
		}
		if (pFood == NULL) {
			pFood = mkFood();
			pNext->pNext = pFood;
		}
		printSnake();
	}
	Lock = 0;
	return;
}
