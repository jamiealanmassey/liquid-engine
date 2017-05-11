#include "Logger.h"
#include <fstream>

namespace liquid {
namespace utilities {

    Logger::Logger()
    {
    }

    Logger::~Logger()
    {
    }

    void Logger::log(std::string text, eSeverityType type)
    {
        mLoggerText.push_back(text);
        mLoggerSeverities.push_back(type);
    }

    void Logger::dumpLoggerToFile()
    {
        std::ofstream stream("logger.txt");
        std::string severity;

        for (uint32_t i = 0; i < mLoggerText.size(); i++)
        {
            if (mLoggerSeverities[i] == eSeverityType::SEVERITYTYPE_INFO)
                severity = "[INFO]    : ";
            else if (mLoggerSeverities[i] == eSeverityType::SEVERITYTYPE_WARNING)
                severity = "[WARNING] : ";
            else if (mLoggerSeverities[i] == eSeverityType::SEVERITYTYPE_ERROR)
                severity = "[ERROR]   : ";

            stream << severity.c_str() << mLoggerText[i].c_str() << "\n";
        }
    }

    static Logger& instance()
    {
        static Logger singleton;
        return singleton;
    }

}}
