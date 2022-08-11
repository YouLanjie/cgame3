#include "../include/head.h"

void Settings() {
	menuData data;

	menuDataInit(&data);
	data.title = "设置";
	data.cfg   = 3;
	data.addText(&data, "秒数", "微秒数", NULL);
	data.addTextData(&data, 0, "%s%s", "%z设置游戏更新间隔的秒数%z", "%z设置游戏更新间隔的微秒数%z");
	data.addTextData(&data, 1, "%s%s", 1, 1);
	data.addTextData(&data, 2, "%s%s", &tick.it_interval.tv_sec, &tick.it_interval.tv_usec);
	data.addTextData(&data, 3, "%s%s", 1, 1000);

	data.menuShow(&data);
	return;
}

