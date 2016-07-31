#ifndef _LOGGER_H
#define _LOGGER_H

#include <vector>
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

class Logger
{
public:
	enum eType
	{
		LOG_ERROR	= 0,
		LOG_WARNING = 1,
		LOG_INFO	= 2,
	};

public:
	Logger();
	~Logger();

	void writeFile();
	void message(std::string msg, eType type);
	bool message(std::string msg, eType type, bool result);

	static Logger& instance();

protected:
	int32_t					 m_NumWarnings;
	int32_t					 m_NumErrors;
	std::vector<std::string> m_Logging;
};

#endif // _LOGGER_H
