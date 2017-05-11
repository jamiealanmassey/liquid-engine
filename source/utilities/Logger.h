#include <vector>

namespace liquid { namespace utilities {
#ifndef _LOGGER_H
#define _LOGGER_H

class Logger
{
public:
    enum eSeverityType
    {
        SEVERITYTYPE_INFO = 0,
        SEVERITYTYPE_WARNING = 1,
        SEVERITYTYPE_ERROR = 2,
    };

public:
    Logger();
    ~Logger();

    void log(std::string text, eSeverityType type);

    void dumpLoggerToFile();

    static Logger& instance();

protected:
    std::vector<std::string> mLoggerText;
    std::vector<eSeverityType> mLoggerSeverities;
};

#endif // _LOGGER_H
}}
