#include <stdio.h>

#include "global.h"

void exit_failure()
{
	asm("mov	$1, %eax \n"
		"mov	$1, %ebx \n"
		"int	$0x80");
}

int read_file(char *filename, char content[], int size)
{
	int i;

	FILE *file;

	file = fopen(filename, "r");
	if(file == NULL)
	{
		printf("ERROR: Could not open file %s\n", filename);
		exit_failure();
	}

	for(i = 0; i<size; i++)
	{
		content[i] = fgetc(file);
		if(content[i] == '\n')
		{
			content[i] = '\0';
			i = size;
		}
	}

	return 0;
}

int string_to_int(char *string)
{
	int  i, n;

	n = 0;

	for(i = 0; string[i] != '\0'; i++)
	{
		n = (n*10)+(string[i]-'0');
	}

	return n;
}

int string_compare(char *string1, char *string2)
{
	int i;

	i = 0;
	while(i >= 0)
	{
		if(string1[i] != string2[i])
			i = -1;
		else
			if(string1[i] != '\0')
				i++;
			else
				i = -2;
	}

	return i;
}

int print_info()
{
	char content[READ_SIZE];
	int current;
	int maximum;
	int percent;

	read_file("/sys/class/power_supply/"ADAPTER"/charge_now" , content, READ_SIZE);
	current = string_to_int(content);

	read_file("/sys/class/power_supply/"ADAPTER"/charge_full", content, READ_SIZE);
	maximum = string_to_int(content);

	read_file("/sys/class/power_supply/"ADAPTER"/status", content, READ_SIZE);
	if(string_compare(content, "Charging\0") == -2)
		printf(P_CHAR P_SEPA);
	else if(string_compare(content, "Discharging\0") == -2)
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

