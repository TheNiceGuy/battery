#include <stdio.h>

#include "global.h"

int read_file(char *filename, char content[], int size) {
	int i;

	FILE *file;

	file = fopen(filename, "r");
	if(file == NULL) {
		#if DEBUG
		printf("ERROR: Could not open file %s\n", filename);
		#endif
		return 1;
	}

	for(i = 0; i<size; i++) {
		content[i] = fgetc(file);
		if(content[i] == '\n') {
			content[i] = '\0';
			i = size;
		}
	}

	fclose(file);

	return 0;
}

int string_to_int(char *string) {
	int  i, n;

	n = 0;

	for(i = 0; string[i] != '\0'; i++)
		n = (n*10)+(string[i]-'0');

	return n;
}

int string_compare(char *string1, char *string2) {
	int i;

	i = 0;
	while(i >= 0) {
		if(string1[i] != string2[i])
			i = B_FALSE;
		else
			if(string1[i] != '\0')
				i++;
		else
			i = B_TRUE;
	}

	return i;
}

int print_info() {
	char content[READ_SIZE];
	long current;
	long maximum;
	long percent;
	int ret;

	ret = read_file("/sys/class/power_supply/"ADAPTER"/"CHECK1"_now" , content, READ_SIZE);
	if(ret == 1)
		read_file("/sys/class/power_supply/"ADAPTER"/"CHECK2"_now" , content, READ_SIZE);
	current = string_to_int(content);

	ret = read_file("/sys/class/power_supply/"ADAPTER"/"CHECK1"_full", content, READ_SIZE);
	if(ret == 1)
		read_file("/sys/class/power_supply/"ADAPTER"/"CHECK2"_full", content, READ_SIZE);
    
	maximum = string_to_int(content);

	read_file("/sys/class/power_supply/"ADAPTER"/status", content, READ_SIZE);
	if(string_compare(content, "Charging\0") == B_TRUE)
		printf(P_CHAR P_SEPA);
	else if(string_compare(content, "Discharging\0") == B_TRUE)
		printf(P_DISC P_SEPA);
	else
		printf(P_FULL P_SEPA);

	percent = 100*current/maximum;
	printf("%ld%%\n", percent);

	return 0;
}

int main() {
	print_info();

	return 0;
}

