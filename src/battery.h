#ifndef BATTERY_H
#define BATTERY_H

typedef enum
{
	CHARGING,
	DISCHARGING,
	FULL
} status;

typedef struct battery
{
	int current;
	int maximum;
	int percent;
	int status;
} battery;

int get_info(battery *bat);
int get_percent(battery *bat);

#endif
