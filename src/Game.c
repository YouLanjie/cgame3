#include "../include/head.h"
#include <stdio.h>

void Game() {
	struct Snake * pHead = NULL, * pNew = NULL, * pEnd = NULL;
	struct winsize size;
	short way = Up, way2= Up;
	int Long = 4;

	printf("暂未开发\n");
	Input();
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	pHead = pNew = pEnd = (struct Snake *)malloc(sizeof(struct Snake));
	pNew -> size[0] = (size.ws_col / 2);
	pNew -> size[1] = (size.ws_row / 2);
	for (int i = 1; i < 4; i++) {
		pNew = (struct Snake *)malloc(sizeof(struct Snake));
		pNew -> size[0] = (size.ws_col / 2);
		pNew -> size[1] = (size.ws_row / 2 + i);
		pEnd -> pNext = pNew;
		pEnd = pNew;
	}
	while(1) {
		Clear2
		KbhitNoTime();
		pNew = pHead;
		if(pNew -> size[0] < 0 || pNew -> size[1] < 0) {
			printf("error!!!!!!\n");
			Input();
			return;
		}
		for (int i = 0; i < Long; i++) {
			if (i == 0) {
				printf("\033[%d;%dH@", pNew -> size[1], pNew -> size[0]);
			}
			else {
				printf("\033[%d;%dH#", pNew -> size[1], pNew -> size[0]);
			}
			printf("\033[s\033[%d;1H%d:\t x:%d\ty:%d\033[u",i + 1, i, pNew -> size[0], pNew -> size[1]);
			if (pNew -> pNext != NULL) {
				pEnd = pNew;
				pNew = pNew -> pNext;
			}
		}
		KbhitNoTime();
		// sleep(1);
		way2 = way;
		way = 0;
		for (int i = 0;i <= 250000 && way == 0; i++) {
			way = KbhitNoTime();
		}
		if (way != 0) {
			getchar();
			way = KbhitHas();
			if (way != 0) {
				getchar();
				way = getchar();
			}
			else {
				return;
			}
		}
		else {
			KbhitNoTime();
			way = way2;
		}
		switch (way) {
			case Up:
			case 'A':
				if (way != Down && way != 'B') {
					pNew -> size[1] = (pHead -> size[1]) - 1;
					way = Up;
				}
				break;
			case Down:
			case 'B':
				if (way != Up && way != 'A') {
					pNew -> size[1] = (pHead -> size[1]) + 1;
					way = Down;
				}
				break;
			case Left:
			case 'D':
				if (way != Right && way != 'C') {
					pNew -> size[0] = (pHead -> size[0]) - 1;
					way = Left;
				}
				break;
			case Right:
			case 'C':
				if (way != Left && way != 'D') {
					pNew -> size[0] = (pHead -> size[0]) + 1;
					way = Right;
				}
				break;
			default:
				pNew -> size[1] = (pHead -> size[1]) - 1;
				way = way2;
		}
		pNew -> pNext = pHead;
		pEnd -> pNext = NULL;
		pHead = pNew;
	}
	Input();
	free(pHead);
	return;
}
