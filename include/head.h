#include "include.h"
#include <sys/ioctl.h>

struct Snake {
	short size[2];
	struct Snake * pNext;
};

enum Way{Up = 49, Right, Down, Left};

void Game();
void Top();
void stop();

