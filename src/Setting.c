#include "../include/head.h"

void Settings()
{
	ctools_menu_t * data = NULL;

	ctools_menu_t_init(&data);

	data->title = "设置";
	data->cfg = 3;
	ctools_menu_AddText(data, "秒数", "微秒数", NULL);
	ctools_menu_AddTextData(data, ctools_menu_TextDataDescribe, "%s%s",
			 "设置游戏更新间隔的秒数",
			 "设置游戏更新间隔的微秒数");
	ctools_menu_AddTextData(data, ctools_menu_TextDataSetType, "%s%s", 1, 1);
	ctools_menu_AddTextData(data, ctools_menu_TextDataSetVar, "%s%s",
			 &tick.it_interval.tv_sec, &tick.it_interval.tv_usec);
	ctools_menu_AddTextData(data, ctools_menu_TextDataSetFoot, "%s%s", 1, 1000);
	ctools_menu_AddTextData(data, ctools_menu_TextDataSetMin, "%s%s", 0, 0);

	ctools_menu_Show(data);
	return;
}
