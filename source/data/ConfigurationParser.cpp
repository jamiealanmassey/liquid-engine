#include "ConfigurationParser.h"

namespace liquid {
namespace data {

    ConfigurationParser::ConfigurationParser()
    {}

    ConfigurationParser::~ConfigurationParser()
    {
        mData.clear();
    }

    bool ConfigurationParser::parseFile(std::string file)
    {
        std::ifstream fileStream;
        fileStream.open(file);

        int32_t extPosition = file.find_last_of(".");
        std::string ext = file.substr(extPosition + 1);

        if (extPosition == std::string::npos || fileStream.is_open() == false ||
            (ext.compare("cfg") != 0 || ext.compare("config") != 0))
        {
            return false;
        }

        std::string nextLine = "";
        std::vector<std::string> lines;
        
        while (std::getline(fileStream, nextLine)) 
            lines.push_back(nextLine);

        compileData(lines);
        fileStream.close();
        return true;
    }

    bool ConfigurationParser::parseString(std::string str)
    {
        char delim = '\n';
        std::vector<std::string> lines;

        for (size_t p = 0, q = 0; p != str.npos; p = q)
        {
            lines.push_back(str.substr(p + (p != 0), 
                (q = str.find(delim, p + 1)) - p - (p != 0)));
        }

        compileData(lines);
        return true;
    }

    std::string ConfigurationParser::getValueAsString(std::string name) const
    {
        std::map<std::string, std::string>::const_iterator it = mData.find(name);
        if (it == mData.end())
            return "";
        
        return it->second;
    }

    int32_t ConfigurationParser::getValueAsInteger32(std::string name) const
    {
        std::map<std::string, std::string>::const_iterator it = mData.find(name);
        if (it == mData.end())
            return 0;

        return std::stoi(it->second);
    }

    float ConfigurationParser::getValueAsFloat(std::string name) const
    {
        std::map<std::string, std::string>::const_iterator it = mData.find(name);
        if (it == mData.end())
            return 0.0f;

        return std::stof(it->second);
    }

    bool ConfigurationParser::getValueAsBoolean(std::string name) const
    {
        std::map<std::string, std::string>::const_iterator it = mData.find(name);
        if (it == mData.end())
            return false;

        std::string value = it->second;
        std::transform(value.begin(), value.end(), value.begin(), ::toupper);
        
        if (value == "0" || value == "FALSE")
            return false;
        else if (value == "1" || value == "TRUE")
            return true;
        else
            return false;
    }

    uint32_t ConfigurationParser::getDataCount() const
    {
        return mData.size();
    }

    const std::map < std::string, std::string>& ConfigurationParser::getData() const
    {
        return mData;
    }

    void ConfigurationParser::compileData(std::vector<std::string> lines)
    {
        for (auto ln : lines)
        {
            std::vector<std::string> tokens;
            std::istringstream iss(ln);
            std::copy(std::istream_iterator<std::string>(iss),
                std::istream_iterator<std::string>(),
                std::back_inserter(tokens));

            if (tokens.empty() == false && tokens[0].compare("--") != 0)
            {
                std::string name = tokens[0];
                std::string value = tokens[1];

                if (mData.find(name) == mData.end())
                    mData[name] = value;
            }
        }
    }

}}
