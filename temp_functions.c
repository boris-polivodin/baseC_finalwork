#include "temp_functions.h"

const int COLUMNS = 6;

size_t getLineCount(char file_name[]) {
	FILE* in = fopen(file_name, "r");
	if ( in == NULL ) {
		perror( "Ошибка при открытии исходного файла" );
		exit(1);
	}

	size_t counter = 0; // предполагаем, что строк ноль в файле - т.е. пустой
	int ch, pre = EOF; // текущий символ, последний считаный символ

	// в цикле считаем сколько переводов строки в файле и запоминаем это в переменную counter
	// если файл пустой, то тело цикла не выполнится ни разу, так как первый считанный символ будет как раз EOF
	// и в pre останется EOF
	while ((ch = fgetc(in)) != EOF) { // в цикле проходим весь файл посимвольно
		pre = ch; // запоминаем последний считаный символ
		if ( ch == '\n' ) // если нашли перевод строки,
			++counter; // то увеличиваем счетчик строк
	}

	// весь смысл переменной pre в том, чтобы запомнить какой символ мы считали перед тем как наткнулись на EOF в файле
	// или в pre будет EOF - если тело цикла ни разу не выполнилось, это будет при пустом файле
	// последняя строка файла может заканчиваться не \n, а строку посчитать надо - вот для этого и нужна переменная pre

	if (pre == EOF) // если файл пустой
		puts( "Файл пустой!" ); // выводим информацию об этом
	else if (pre != '\n') { // если pre содержит в себе не перевод строки, и файл не пустой
		++counter; // то увеличиваем счетчик строк
	}
	fclose(in);

	putchar('\n');
		// выводим на экран информацию о количестве строк
//	printf("%s %s = %lu\n", "Строк в файле", FNAME, counter);
	return counter;
}

size_t input(Sensor *s, char file_name[]) {

	FILE *in;
	in = fopen(file_name, "r");
	if (in == NULL) {
		printf("Error occured while opening input file!");
		exit(1);
	}

	int read = 0;
	size_t index = 0;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	int8_t t;

	while (!feof(in)) {
		read = fscanf(in
				, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd"
				, &year
				, &month
				, &day
				, &hour
				, &minute
				, &t);

		if (read == COLUMNS) {
			s[index].year = year;
			s[index].month = month;
			s[index].day = day;
			s[index].hour = hour;
			s[index].minute = minute;
			s[index].t = t;

			index++;
		} else {
			char str[32];
			read = fscanf(in, "%[^\n]", str);
			printf("ERROR item=%s in line=%ld\n", str, index + 1);
		}

		if (ferror(in)) {
			printf("Error reading input file!");
			exit(1);
		}

	}

	fclose(in);

	return index;

}

void average_monthly(Sensor *sensor, size_t number) {

	uint16_t year = sensor[0].year;
	uint8_t month = sensor[0].month;
	float sum = 0;
	uint16_t counter = 0;

	for (size_t i = 0; i < number; ++i) {
		if (sensor[i].year == year && sensor[i].month == month) {
			sum += sensor[i].t;
			counter++;
		} else {
			if (counter > 0) {
				printf("For year:%hu, month:%hhu - average=%.3f\n", year, month, sum / counter);
			}

			year = sensor[i].year;
			month = sensor[i].month;
			sum = sensor[i].t;
			counter = 1;
		}
	}

	if (counter > 0) {
		printf("For year:%hu, month:%hhu - average=%.3f\n", year, month, sum / counter);
	}

}

void average_yearly(Sensor *sensor, size_t number) {

	float sum = 0;

	for (size_t i = 0; i < number; ++i) {
		sum += sensor[i].t;
	}

	printf("average yearly=%.3f\n", sum / number);

}

void min_t_for_month(Sensor *sensor, size_t number, uint8_t month) {
	int8_t min = INT8_MIN;
	for (size_t i = 0; i < number; ++i) {
		if (sensor[i].month == month) {
			if (min == INT8_MIN) {
				min = sensor[i].t;
			} else if (sensor[i].t < min){
				min = sensor[i].t;
			}
		}
	}
	printf("In %hhu month min t=%hhd\n", month, min);
}

void max_t_for_month(Sensor *sensor, size_t number, uint8_t month) {
	int8_t max = INT8_MAX;
	for (size_t i = 0; i < number; ++i) {
		if (sensor[i].month == month) {
			if (max == INT8_MAX) {
				max = sensor[i].t;
			} else if (sensor[i].t > max) {
				max= sensor[i].t;
			}
		}
	}
	printf("In %hhu month max t=%hhd\n", month, max);
}

void t_yearly_min(Sensor *sensor, size_t number) {
	int8_t min = INT8_MAX;
	for (size_t i = 0; i < number; ++i) {
		if (sensor[i].t < min){
			min = sensor[i].t;
		}
	}
	printf("yearly minimum t=%hhd\n", min);
}

void t_yearly_max(Sensor *sensor, size_t number) {
	int8_t max = INT8_MIN;
	for (size_t i = 0; i < number; ++i) {
		if (sensor[i].t > max){
			max = sensor[i].t;
		}
	}
	printf("yearly maximum t=%hhd\n", max);
}
