#include <stdio.h>

//структура где будем хранить данные
struct dateBirth {
	int day;
	int month;
	int year;
	int hour;
	int minute;
};

int authentMonth(int nomber){
	if (nomber == 1 || nomber == 3 || nomber == 5 || nomber == 7 || nomber == 8 || nomber == 10 || nomber == 12){
		return 2;
	}
	else{
		if (nomber == 2){
			return 0;
		}
		else
			return 1;
	}
}
//функция для проверки года на высокосность
int isYearVis(int year){
	if (year % 4 == 0){
		if (year % 100 == 0){
			if (year % 400 == 0){
				return 1;
			}
			else{
				return 0;
			}
		}
		else
			return 1;
	}
	else
		return 0;
}

#define SEC_IN_MINUTE 60
#define MINUTS_IN_HOUR 60
#define HOURS_IN_DAY 24
#define LONG_MONTH 31
#define SHORT_MONTH 30
#define LONG_YEAR 366
#define SHORT_YEAR 365

int main(){
	struct dateBirth date;
	int curYear = 2017;
	int allSeconds = 0;
	int allMinutes = 0; // хранит кол-во минут < 60
	int allHours = 0; // хранит кол-во часо < 24
	int allDays = 0;


	printf("Input your age in format dd.mm.yyyy hh:mm ");
	scanf("%d.%d.%d %d:%d", &date.day, &date.month, &date.year, &date.hour, &date.minute);

	allMinutes = MINUTS_IN_HOUR - date.minute;
	date.hour++;
	allHours = HOURS_IN_DAY - date.hour;
	date.day++;

	if (authentMonth(date.month) == 1){
		allDays = LONG_MONTH + 1 - date.day;
	}
	else{
		if (authentMonth(date.month) == 0){
			if (isYearVis(date.year) == 1)
				allDays = 28 + 1 - date.day;
			else
				allDays = 27 + 1 - date.day;
		}
		else
			allDays = SHORT_MONTH + 1 - date.day;
	}
	date.month++;

	for (int i = date.month; i <= 12; i++){
		if (authentMonth(date.month) == 0){
			if (isYearVis(date.year) == 1)
				allDays += 28;
			else
				allDays += 27;
		}
		if (authentMonth(date.month) == 1)
			allDays += SHORT_MONTH;
		if (authentMonth(date.month) == 2)
			allDays += LONG_MONTH;
	}
	date.year++;

	for (int i = date.year; i < curYear; i++){
		if (isYearVis(i) == 1)
			allDays += LONG_YEAR;
		else
			allDays += SHORT_YEAR;
	}

	allSeconds = (((allDays * HOURS_IN_DAY) + allHours) * MINUTS_IN_HOUR + allMinutes) * SEC_IN_MINUTE;
	printf("Your life is %d seconds from your birth to current year", allSeconds);

}
