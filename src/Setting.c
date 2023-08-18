#include "../include/head.h"

const extern ctools_menu CT_MENU;

void Settings()
{
	const ctools_menu *m = &CT_MENU;
	struct ctools_menu_t *data;

	m->data_init(&data);
	m->set_title(data, "设置");
	m->set_type(data, "setting");
	m->set_text(data, "秒数", "微秒数", NULL);
	m->set_text_data(data, "describe", "%s%s",
			 "设置游戏更新间隔的秒数",
			 "设置游戏更新间隔的微秒数");
	m->set_text_data(data, "type", "%s%s", 1, 1);
	m->set_text_data(data, "var", "%s%s",
			 &tick.it_interval.tv_sec, &tick.it_interval.tv_usec);
	m->set_text_data(data, "foot", "%s%s", 1, 1000);
	m->set_text_data(data, "min", "%s%s", 0, 0);

	m->show(data);
	return;
}
