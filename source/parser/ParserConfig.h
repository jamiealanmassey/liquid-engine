#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iterator>

namespace liquid { namespace parser {
#ifndef _PARSERCONFIG_H
#define _PARSERCONFIG_H

/**
 * \class ParserConfig
 *
 * \ingroup Data
 * \brief Parses generic configuration files into usable data
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/04/2017
 *
 */

class ParserConfig : public Parser
{
public:
    /// ConfigurationParser Constructor
    ParserConfig();

    /// ConfigurationParser Destructor
    ~ParserConfig();

    /** \brief Parses the given file into paired <string, string> data
      * \param file Name of the file appended to the path of the file, relative to game executable
      * \return True if the file was parsed correctly, False otherwise
      *
      * Takes the file at the given location and parses each line into a std::vector,
      * that vector is then passed to ConfigurationParser::compileData(lines) which
      * puts the data into mData as <key, value> pairs.
      */
    virtual void parseFile(std::string file) override;

    /** \brief Parses the given string into paired <string, string> data
      * \param str std::string which contains information about configuration values
      * \return True if the file was parsed correctly, False otherwise
      *
      * Takes the given std::string and then parses each line into a std::vector,
      * that vector is then passed to ConfigurationParser::compileData(lines) which
      * puts the data into mData as <key, value> pairs.
      */
    virtual void parseString(std::string str) override;

protected:
    /** \brief Compiles the given collection of lines into a std::map
      * \param lines Collection of lines you want to compile
      *
      * Takes the given collection of lines and methodically parses through them
      * creating tokens where the first token is the name of the key and the second
      * value after whitespace is the value of the key.
      */
    void compileData(std::vector<std::string> lines);
};

#endif // _CONFIGURATIONPARSER_H
}}
