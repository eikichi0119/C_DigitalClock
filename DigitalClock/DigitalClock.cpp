// DigitalClock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#define WIN32_LEAN_AND_MEAN
#include <stdint.h> // portable: uint64_t   MSVC: __int64 
#include <iomanip>

// MSVC defines this in winsock2.h!?
//typedef struct timeval {
//	long tv_sec;
//	long tv_usec;
//} timeval;

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
	// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
	// This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
	// until 00:00:00 January 1, 1970 
	static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

	SYSTEMTIME  system_time;
	FILETIME    file_time;
	uint64_t    time;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	time = ((uint64_t)file_time.dwLowDateTime);
	time += ((uint64_t)file_time.dwHighDateTime) << 32;

	tp->tv_sec = (long)((time - EPOCH) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
	return 0;
}

int main()
{
	while (1) {
		timeval curTime;
		gettimeofday(&curTime, NULL);
		struct timestruct {
			char currentTime[84] = "";
			char buffer[80];
			int milli;
		};

		timestruct a;
		a.milli = curTime.tv_usec / 1000;

		//timeval curTime;
		//gettimeofday(&curTime, NULL);
		//int milli = curTime.tv_usec / 1000;

		time_t rawtime;
		struct tm  timeinfo;
		//char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(a.buffer, 80, "%Y-%m-%d %H:%M:%S", &timeinfo);

		//char currentTime[84] = "";
	
		std::cout << a.currentTime << a.buffer << ":" << std::setw(3) << std::setfill('0') << a.milli << std::endl;
		Sleep(100);
		system("Cls");
	}
	
//	std::cout << "current time:" << currentTime << std::endl;
}