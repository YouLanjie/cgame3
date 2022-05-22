#include "../include/head.h"
#include <sys/time.h>

static int GetNowTime();

void Game() {
	struct Snake * pHead = NULL, * pNew = NULL, * pEnd = NULL, * pFood = NULL;
	struct winsize size;
	short way = Up, way2= Up, BORE = 1;
	int Long = 4;
	long int usec = 0;
	FILE * fp;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	pHead = pNew = pEnd = (struct Snake *)malloc(sizeof(struct Snake));
	pNew -> size[0] = size.ws_col / 2;
	pNew -> size[1] = size.ws_row / 2;
	for (int i = 1; i < 4; i++) {
		pEnd = pNew;
		pNew = (struct Snake *)malloc(sizeof(struct Snake));
		pNew -> size[0] = size.ws_col / 2;
		pNew -> size[1] = size.ws_row / 2 + i;
		pEnd -> pNext = pNew;
	}
	if (pFood == NULL) {
		pFood = (struct Snake *)malloc(sizeof(struct Snake));
		srand(time(NULL));
		pFood -> size[0] = rand() % size.ws_col + 1;
		pFood -> size[1] = rand() % size.ws_row + 1;
		pNew -> pNext = pFood;
	}
	Clear2
	while(1) {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		
		Clear
		kbhitGetchar();
		if (pFood == NULL) {
			pFood = (struct Snake *)malloc(sizeof(struct Snake));
			srand(time(NULL));
			pFood -> size[0] = rand() % size.ws_col + 1;
			pFood -> size[1] = rand() % size.ws_row + 1;
			pEnd -> pNext -> pNext = pFood;
		}
		pNew = pHead;
		printf("\033[s\033[1;1H长度:%6d\n分数:%6d\033[u", Long, (Long - 4) * 10);
		printf("\033[%d;%dH\033[1;32m@\033[0m", pNew -> size[1], pNew -> size[0]);
		if (pNew -> size[0] < 1 || pNew -> size[1] < 1 || pNew -> size[0] > size.ws_col || pNew -> size[1] > size.ws_row) {
			Clear
			kbhitGetchar();
			printf("\033[9;%dH\033[1;31mYou die您已死亡\033[0m\n",size.ws_col / 2 - 7);
			Menu3(" ");
			getch();
			free(pHead);
			break;
		}
		pEnd = pNew;
		pNew = pNew -> pNext;
		for (int i = 1; i < Long; i++) {
			printf("\033[%d;%dH\033[1;33m#\033[0m", pNew -> size[1], pNew -> size[0]);
			if (pNew -> size[0] == pHead -> size[0] && pNew -> size[1] == pHead -> size[1]) {
				Clear
				kbhitGetchar();
				printf("\033[9;%dH\033[1;31mYou die您已死亡\033[0m\n",size.ws_col / 2 - 7);
				Menu3(" ");
				getch();
				free(pHead);
				fp = fopen("top.txt","a");
				if (fp) {
					fprintf(fp, "%d %d\n",Long,(Long - 4) * 10);
					fclose(fp);
				}
				return;
			}
			if (i + 1 < Long) {
				pEnd = pNew;
				pNew = pNew -> pNext;
			}
		}
		printf("\033[%d;%dH\033[1;36m%%\033[0m", pNew -> pNext -> size[1], pNew -> pNext -> size[0]);
		kbhitGetchar();
		way2 = way;
		way = 0;
		usec = GetNowTime();
		while (usec + 50000 >= GetNowTime()) {
			way = kbhitGetchar();
			system("sleep 0.005");
		}
		if (way != 0) {
			getchar();
			if (way == 0x1B) {
				if (kbhit() != 0) {
					getchar();
					way = getchar();
				}
				else {
					Clear
					printf("\033[9;%dH\033[1;31m按下Esc\033[0m\n", size.ws_col / 2 - 3);
					Menu3(" ");
					getch();
					free(pHead);
					break;
				}
			}
			else if (way == 'q' || way == 'Q') {
				Clear
				printf("\033[9;%dH\033[1;31m按下Q\033[0m\n", size.ws_col / 2 - 2);
				Menu3(" ");
				getch();
				free(pHead);
				break;
			}
		}
		else {
			kbhitGetchar();
			way = way2;
		}
		BORE = 1;            //布尔值，仅用于循环判断
		while (BORE){
			BORE = 0;
			switch (way) {
				case Up:
				case 'k':
				case 'w':
				case 'A':
					if (way2 != Down && way2 != 'B') {
						if (pHead -> size[0] == pFood -> size[0] && pHead -> size[1] - 1 == pFood -> size[1]) {
							pFood -> size[1] = pNew -> size[1];
							pFood -> size[0] = pNew -> size[0];
							pEnd -> pNext = pFood;
							pFood = NULL;
							Long++;
						}
						pNew -> size[1] = pHead -> size[1] - 1;
						pNew -> size[0] = pHead -> size[0];
						way = Up;
						way2 = Up;
					}
					else {
						if (pHead -> size[0] == pFood -> size[0] && pHead -> size[1] + 1 == pFood -> size[1]) {
							pFood -> size[1] = pNew -> size[1];
							pFood -> size[0] = pNew -> size[0];
							pEnd -> pNext = pFood;
							pFood = NULL;
							Long++;
						}
						pNew -> size[1] = pHead -> size[1] + 1;
						pNew -> size[0] = pHead -> size[0];
						way = Down;
						way2 = Down;
					}
					break;
				case Down:
				case 'j':
				case 's':
				case 'B':
					if (way2 != Up && way2 != 'A') {
						if (pHead -> size[0] == pFood -> size[0] && pHead -> size[1] + 1 == pFood -> size[1]) {
							pFood -> size[1] = pNew -> size[1];
							pFood -> size[0] = pNew -> size[0];
							pEnd -> pNext = pFood;
							pFood = NULL;
							Long++;
						}
						pNew -> size[1] = pHead -> size[1] + 1;
						pNew -> size[0] = pHead -> size[0];
						way = Down;
						way2 = Down;
					}
					else {
						if (pHead -> size[0] == pFood -> size[0] && pHead -> size[1] - 1 == pFood -> size[1]) {
							pFood -> size[1] = pNew -> size[1];
							pFood -> size[0] = pNew -> size[0];
							pEnd -> pNext = pFood;
							pFood = NULL;
							Long++;
						}
						pNew -> size[1] = pHead -> size[1] - 1;
						pNew -> size[0] = pHead -> size[0];
						way = Up;
						way2 = Up;
					}
					break;
				case Left:
				case 'h':
				case 'a':
				case 'D':
					if (way2 != Right && way2 != 'C') {
						if (pHead -> size[0] - 1 == pFood -> size[0] && pHead -> size[1] == pFood -> size[1]) {
							pFood -> size[1] = pNew -> size[1];
							pFood -> size[0] = pNew -> size[0];
							pEnd -> pNext = pFood;
							pFood = NULL;
							Long++;
						}
						pNew -> size[0] = pHead -> size[0] - 1;
						pNew -> size[1] = pHead -> size[1];
						way = Left;
						way2 = Left;
					}
					else {
						if (pHead -> size[0] + 1 == pFood -> size[0] && pHead -> size[1] == pFood -> size[1]) {
							pFood -> size[1] = pNew -> size[1];
							pFood -> size[0] = pNew -> size[0];
							pEnd -> pNext = pFood;
							pFood = NULL;
							Long++;
						}
						pNew -> size[0] = pHead -> size[0] + 1;
						pNew -> size[1] = pHead -> size[1];
						way = Right;
						way2 = Right;
					}
					break;
				case Right:
				case 'l':
				case 'd':
				case 'C':
					if (way2 != Left && way2 != 'D') {
						if (pHead -> size[0] + 1 == pFood -> size[0] && pHead -> size[1] == pFood -> size[1]) {
							pFood -> size[1] = pNew -> size[1];
							pFood -> size[0] = pNew -> size[0];
							pEnd -> pNext = pFood;
							pFood = NULL;
							Long++;
						}
						pNew -> size[0] = pHead -> size[0] + 1;
						pNew -> size[1] = pHead -> size[1];
						way = Right;
						way2 = Right;
					}
					else {
						if (pHead -> size[0] + 1 == pFood -> size[0] && pHead -> size[1] == pFood -> size[1]) {
							pFood -> size[1] = pNew -> size[1];
							pFood -> size[0] = pNew -> size[0];
							pEnd -> pNext = pFood;
							pFood = NULL;
							Long++;
						}
						pNew -> size[0] = pHead -> size[0] - 1;
						pNew -> size[1] = pHead -> size[1];
						way = Left;
						way2 = Left;
					}
					break;
				default:
					way = way2;
					BORE = 1;
					break;
			}
		}
		way = way2;
		if (pFood != NULL) {
			pEnd -> pNext = pFood;
		}
		pNew -> pNext = pHead;
		pHead = pNew;
	}
	fp = fopen("top.txt","a");
	if (fp) {
		fprintf(fp, "%d %d\n",Long,(Long - 4) * 10);
		fclose(fp);
	}
	return;
}

static int GetNowTime() {
	struct timeval time;

	gettimeofday(&time, NULL);
	return time.tv_usec;
}
