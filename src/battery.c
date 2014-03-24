#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "battery.h"

int get_info(battery *bat)
{
	char content[READ_SIZE];

	read_file("/sys/class/power_supply/"ADAPTER"/charge_now" , content, READ_SIZE);
	bat->current = atoi(content);

	read_file("/sys/class/power_supply/"ADAPTER"/charge_full", content, READ_SIZE);
	bat->maximum = atoi(content);

	bat->percent = get_percent(bat);
	read_file("/sys/class/power_supply/"ADAPTER"/status", content, READ_SIZE);

	if(strcmp(content, "Charging\n") == 0)
		bat->status = CHARGING;
	else if(strcmp(content, "Discharging\n") == 0)
		bat->status = DISCHARGING;
	else
		bat->status = FULL;

	return 0;
}

int get_percent(battery *bat)
{
	return (100*bat->current/bat->maximum);
}
