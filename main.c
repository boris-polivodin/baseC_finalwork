#include <stdio.h>
#include <unistd.h>
#include "temp_functions.h"

#define ROWS 527040
int main(int argc, char *argv[]) {

	char file_name[] = "temperature_small.csv";
	int rez=0, month = 0, help_only = 1;
	while ( (rez = getopt(argc,argv,"hf:m::")) != -1) {
		switch (rez) {
		case 'h':
			printf("This help for processing of files with temperature indicators.\n\
	Use parameter -f for setting file's name. Default name: temperature_small.csv\n\
	Use parameter -m for setting month.\n");
			printf("For example: sens -f%s -m%d\n", "temperature_big.csv", 1);
			break;
		case 'f':
			strcpy(file_name, optarg);
			printf("Setting file name \"f = %s\".\n", optarg);
			help_only = 0;
			break;
		case 'm':
			month = atoi(optarg);
			printf("Setting month number \"m = %s\".\n", optarg);
			help_only = 0;
			break;
		case '?':
			printf("Error parameter!\n");;
			break;
		};
	}

	if (help_only) {
		return 0;
	}
	//size_t ROWS = getLineCount(file_name);
	Sensor sensor[ROWS]; //= malloc(ROWS * (int) sizeof(Sensor));
	size_t size;
	size = input(sensor, file_name);

	average_monthly(sensor, size);

	if (month >=1 && month <= 12) {
		min_t_for_month(sensor, size, month);
		max_t_for_month(sensor, size, month);
	}

	average_yearly(sensor, size);
	t_yearly_min(sensor, size);
	t_yearly_max(sensor, size);

	return 0;
}
