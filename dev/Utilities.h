#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <string>

static const char* extract_version(const char* full)
{
	std::string p1 = full;
	static std::string p2;
	p2.clear();
	p2 = p1.substr(
		p1.find_last_of("/\\") + 1,
		(p1.length() - p1.find_last_of("/\\") - (p1.length() - p1.find_last_of(".") +1)
	));

	return p2.c_str();
}
#ifdef DEBUG

static void write_log(const char* msg)
{
	time_t now = time(0);
	char* date = ctime(&now);

	std::ofstream logs;
	logs.open("logs.txt", std::ofstream::app | std::ofstream::out);
	logs << msg << " " << date;
	logs.close();
}
#else
static void write_log(const char* msg)
{
}
#endif

#endif UTILITIES_H