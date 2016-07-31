#include "Logger.h"

Logger::Logger() :
	m_NumErrors(0),
	m_NumWarnings(0)
{
}

Logger::~Logger()
{
	writeFile();
}

void Logger::writeFile()
{
	std::ofstream stream("log.txt");

	if (stream.is_open())
	{
		for (auto message : m_Logging)
			stream << message << std::endl;

		stream << std::endl;
		stream << m_NumErrors << " error(s)" << std::endl;
		stream << m_NumWarnings << " warning(s)" << std::endl;

		stream.close();
	}
}

void Logger::message(std::string msg, eType type)
{
	struct tm newtime;
	time_t long_time;

	time(&long_time);
	localtime_s(&newtime, &long_time);

	// Sample hours, mins and secs
	int32_t hour = newtime.tm_hour;
	int32_t mins = newtime.tm_min;
	int32_t secs = newtime.tm_sec;

	// Compile start of error message
	std::string str = "[" + std::to_string(hour) + ":" + std::to_string(mins);
	str += ":" + std::to_string(secs) + "] ";

	// Output depending on error and warnings
	if (type == eType::LOG_ERROR)
	{
		str += "Error - ";
		m_NumErrors++;
	}
	else if (type == eType::LOG_WARNING)
	{
		str += "Warning - ";
		m_NumWarnings++;
	}
	else if (type == eType::LOG_INFO)
		str += "Attention - ";

	// Add error message and push back to list
	str += msg;
	m_Logging.push_back(str);

	std::cout << str << std::endl;
}

bool Logger::message(std::string msg, eType type, bool result)
{
	message(msg, type);
	return result;
}

Logger& Logger::instance()
{
	static Logger singleton;
	return singleton;
}
