#include "../include/head.h"

void Settings()
{
	menuData data = menuDataInit();

	data.title = "设置";
	data.cfg = 3;
	data.addText(&data, "秒数", "微秒数", NULL);
	data.addTextData(&data, menuTextDataDescribe, "%s%s",
			 "%z设置游戏更新间隔的秒数%z",
			 "%z设置游戏更新间隔的微秒数%z");
	data.addTextData(&data, menuTextDataSetType, "%s%s", 1, 1);
	data.addTextData(&data, menuTextDataSetVar, "%s%s",
			 &tick.it_interval.tv_sec, &tick.it_interval.tv_usec);
	data.addTextData(&data, menuTextDataSetFoot, "%s%s", 1, 1000);
	data.addTextData(&data, menuTextDataSetMin, "%s%s", 0, 0);

	data.menuShow(&data);
	return;
}
