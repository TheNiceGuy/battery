#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "battery.h"

int main()
{
	battery bat;
	get_info(&bat);

	if(bat.status == CHARGING)
		printf("  up, ");
	else if(bat.status == DISCHARGING)
		printf("down, ");
	else
		printf("full, ");
	printf("%d%%\n", bat.percent);

	return 0;
}

int read_file(char *filename, char content[], int size)
{
	int i;

	FILE *file;

	file = fopen(filename, "r");
	if(file == NULL)
	{
		printf("ERROR: Could not open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	for(i = 0; i<size; i++)
	{
		content[i] = fgetc(file);
		if(content[i] == EOF)
		{
			strcpy(&content[i], "\0");
			i = size;
		}
	}

	return 0;
}
