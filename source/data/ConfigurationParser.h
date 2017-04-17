#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <map>
#include <algorithm>

namespace liquid { namespace data {
#ifndef _CONFIGURATIONPARSER_H
#define _CONFIGURATIONPARSER_H

/**
 * \class ConfigurationParser
 *
 * \ingroup Data
 * \brief Parses generic configuration files into usable data
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/04/2017
 *
 */

class ConfigurationParser
{
public:
    /// ConfigurationParser Constructor
    ConfigurationParser();

    /// ConfigurationParser Destructor
    ~ConfigurationParser();

    /** \brief Parses the given file into paired <string, string> data
      * \param file Name of the file appended to the path of the file, relative to game executable
      * \return True if the file was parsed correctly, False otherwise
      *
      * Takes the file at the given location and parses each line into a std::vector,
      * that vector is then passed to ConfigurationParser::compileData(lines) which
      * puts the data into mData as <key, value> pairs.
      */
    virtual bool parseFile(std::string file);

    /** \brief Parses the given string into paired <string, string> data
      * \param str std::string which contains information about configuration values
      * \return True if the file was parsed correctly, False otherwise
      *
      * Takes the given std::string and then parses each line into a std::vector,
      * that vector is then passed to ConfigurationParser::compileData(lines) which
      * puts the data into mData as <key, value> pairs.
      */
    virtual bool parseString(std::string str);

    /** \brief Gets the value with the given name as an std::string
      * \param name Name of the value (key) you wish to access
      * \return Returns the value, default: ""
      */
    std::string getValueAsString(std::string name) const;

    /** \brief Gets the value with the given name as a int32_t
      * \param name Name of the value (key) you wish to access
      * \return Returns the value, default: 0
      */
    int32_t getValueAsInteger32(std::string name) const;

    /** \brief Gets the value with the given name as a float
      * \param name Name of the value (key) you wish to access
      * \return Returns the value, default: 0.0f
      */
    float getValueAsFloat(std::string name) const;

    /** \brief Gets the value with the given name as a boolean
      * \param name Name of the value (key) you wish to access
      * \return Returns the value, default: false
      */
    bool getValueAsBoolean(std::string name) const;

    /** \brief Gets the total count of data stored in this Parser
      * \return The count of data stored as a int32_t
      */
    uint32_t getDataCount() const;

    const std::map<std::string, std::string>& getData() const;

protected:
    /** \brief Compiles the given collection of lines into a std::map
      * \param lines Collection of lines you want to compile
      *
      * Takes the given collection of lines and methodically parses through them
      * creating tokens where the first token is the name of the key and the second
      * value after whitespace is the value of the key.
      */
    void compileData(std::vector<std::string> lines);

protected:
    std::map<std::string, std::string> mData; ///< Stored key-pair values of the configuration variables
};

#endif // _CONFIGURATIONPARSER_H
}}
