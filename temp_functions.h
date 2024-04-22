#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct Sensor {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	int8_t t;
} Sensor;

size_t getLineCount(char file_name[]);
size_t input(Sensor *s, char file_name[]);
void average_monthly(Sensor *sensor, size_t number);
void average_yearly(Sensor *sensor, size_t number);
void min_t_for_month(Sensor *sensor, size_t number, uint8_t month);
void max_t_for_month(Sensor *sensor, size_t number, uint8_t month);
void t_yearly_min(Sensor *sensor, size_t number);
void t_yearly_max(Sensor *sensor, size_t number);
