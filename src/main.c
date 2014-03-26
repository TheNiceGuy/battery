#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

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


int print_info()
{
	char content[READ_SIZE];
	int current;
	int maximum;
	int percent;

	read_file("/sys/class/power_supply/"ADAPTER"/charge_now" , content, READ_SIZE);
	current = atoi(content);

	read_file("/sys/class/power_supply/"ADAPTER"/charge_full", content, READ_SIZE);
	maximum = atoi(content);

	read_file("/sys/class/power_supply/"ADAPTER"/status", content, READ_SIZE);
	if(strcmp(content, "Charging\n") == 0)
		printf(P_CHAR P_SEPA);
	else if(strcmp(content, "Discharging\n") == 0)
		printf(P_DISC P_SEPA);
	else
		printf(P_FULL P_SEPA);

	percent = 100*current/maximum;
	printf("%d%%\n", percent);

	return 0;
}

int main()
{
	print_info();

	return 0;
}


