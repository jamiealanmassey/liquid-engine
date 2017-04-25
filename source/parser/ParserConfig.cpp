#include "ParserConfig.h"

namespace liquid {
namespace parser {

    ParserConfig::ParserConfig()
    {}

    ParserConfig::~ParserConfig()
    {
    }

    void ParserConfig::parseFile(std::string file)
    {
        std::ifstream fileStream;
        fileStream.open(file);

        int32_t extPosition = file.find_last_of(".");
        std::string ext = file.substr(extPosition + 1);

        if (extPosition == std::string::npos || fileStream.is_open() == false ||
            (ext.compare("cfg") != 0 || ext.compare("config") != 0))
        {
            return;
        }

        std::string nextLine = "";
        std::vector<std::string> lines;
        
        while (std::getline(fileStream, nextLine)) 
            lines.push_back(nextLine);

        compileData(lines);
        fileStream.close();
        return;
    }

    void ParserConfig::parseString(std::string str)
    {
        char delim = '\n';
        std::vector<std::string> lines;

        for (size_t p = 0, q = 0; p != str.npos; p = q)
        {
            lines.push_back(str.substr(p + (p != 0), 
                (q = str.find(delim, p + 1)) - p - (p != 0)));
        }

        compileData(lines);
    }

    void ParserConfig::compileData(std::vector<std::string> lines)
    {
        ParserNode* node = new ParserNode();

        for (auto ln : lines)
        {
            std::vector<std::string> tokens;
            std::istringstream iss(ln);
            std::copy(std::istream_iterator<std::string>(iss),
                std::istream_iterator<std::string>(),
                std::back_inserter(tokens));

            if (tokens.empty() == false && tokens[0].compare("--") != 0)
            {
                std::string key = tokens[0];
                std::string value = tokens[1];

                node->insertData(key, value);
            }
        }

        mParserNodes.push_back(node);
    }

}}
