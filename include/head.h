#include "tools.h"
#include "specialChar.h"
#include <sys/time.h>

struct Snake {
	short x;
	short y;
	struct Snake * pNext;
};

enum Way{Up = 49, Right, Down, Left};    /* int:49 char:'1' */

void Game();
void Settings();
void stop();

extern struct itimerval tick;

