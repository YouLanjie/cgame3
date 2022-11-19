#include "../include/head.h"

void Settings()
{
	ctools_menu_t * data = NULL;

	ctools_menu_t_init(&data);

	data->title = "设置";
	data->cfg = 3;
	ctools_menu_AddText(data, "秒数", "微秒数", NULL);
	ctools_menu_AddTextData(data, menuTextDataDescribe, "%s%s",
			 "%z设置游戏更新间隔的秒数%z",
			 "%z设置游戏更新间隔的微秒数%z");
	ctools_menu_AddTextData(data, menuTextDataSetType, "%s%s", 1, 1);
	ctools_menu_AddTextData(data, menuTextDataSetVar, "%s%s",
			 &tick.it_interval.tv_sec, &tick.it_interval.tv_usec);
	ctools_menu_AddTextData(data, menuTextDataSetFoot, "%s%s", 1, 1000);
	ctools_menu_AddTextData(data, menuTextDataSetMin, "%s%s", 0, 0);

	ctools_menu_Show(data);
	return;
}
