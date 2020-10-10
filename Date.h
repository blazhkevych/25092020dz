#pragma once
#include <iostream>
#include <iomanip>
class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date() :Date(0, 0, 0) {};
	Date(int day, int month, int year) :
		day(day), month(month), year(year) {};

	friend std::ostream& operator<<(std::ostream& stream, const Date& dt) {
		stream << std::setw(2) << std::setfill('0') << dt.day << '.';
		stream << std::setw(2) << std::setfill('0') << dt.month << '.';
		stream << dt.year;

		return stream;
	};

public:
	int DifferenceYear() const;
};

int Date::DifferenceYear() const
{
	time_t now = time(0);
	struct tm ltm;
	localtime_s(&ltm, &now);

	int currentYear = ltm.tm_year + 1900;
	int currentMonth = ltm.tm_mon + 1;
	int currentDay = ltm.tm_mday;
	int months[] = { 31, 28, 31, 30, 31, 30,
					   31, 31, 30, 31, 30, 31 };

	if (day > currentDay)
		currentMonth--;
	if (month > currentMonth)
		currentYear--;

	return currentYear - year;
}