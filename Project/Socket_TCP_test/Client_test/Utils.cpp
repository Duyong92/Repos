#include "Client.h"

#include <time.h>

string currentTime()
{
	time_t currentTime = time(NULL);
	struct tm* pLocal = localtime(&currentTime);
	int year = pLocal->tm_year;
	int month = pLocal->tm_mon;
	int day = pLocal->tm_mday;
	int hour = pLocal->tm_hour;
	int minute = pLocal->tm_min;
	int second = pLocal->tm_sec;
	return	to_string(year + 1900) + "-" +
		to_string(month + 1) + "-" +
		to_string(day) + " " +
		to_string(hour) + ":" +
		to_string(minute) + ":" +
		to_string(second);
}