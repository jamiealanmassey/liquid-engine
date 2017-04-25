#include <map>
#include <functional>
#include <fstream>
#include <experimental/filesystem>
#include "../parser/ParserConfig.h"

namespace liquid { namespace data {
#ifndef _BINDINGS_H
#define _BINDINGS_H

/**
 * \class Bindings
 *
 * \ingroup Data
 * \brief Defines keyboard, mouse and gamepad bindings in a structure-like class
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/04/2017
 *
 */

class Bindings : public parser::ParserConfig
{
public:
    /// Bindings Constructor
    Bindings();

    /// Bindings Destructor
    ~Bindings();

    /** \brief Parse a file and load bindings data
      * \param file File to parse through
      * \return True if mFuncCallbackConvert exists and file is parsed
      *
      * Puts each <key,value> pair from the ConfigurationParser in the
      * mBindingsData map, whilst also using the mFuncCallbackConvert function
      * callback to map the string input into an integer value that represents
      * the key/button
      */
    virtual void parseFile(std::string file) override;

    /** \brief Loads Bindings from a std::strings
      * \param file Formatted std::string to be parsed
      * \return True if there were no errors, false otherwise
      *
      * Puts each <key,value> pair from the ConfigurationParser in the
      * mBindingsData map, whilst also using the mFuncCallbackConvert function
      * callback to map the string input into an integer value that represents
      * the key/button
      *
      * Note: The std::string needs to be formatted correctly with whitespace
      * between bindings names + values and each line ended with \n
      */
    virtual void parseString(std::string str) override;

    /** \brief Retrieve the value of the specified Binding name
      * \param name Name of the value you want to retrieve
      * \return Integer value of the corresponding bound key
      */
    uint32_t getBindingValue(std::string name);

public:
    std::function<uint32_t(std::string input)> mFuncCallbackConvert; ///< Conversion function to map key names to integers (std::string to uint32_t)

protected:
    std::map<std::string, uint32_t> mBindingsData; ///< Binding data stored as pairs of names and values

private:
    uint32_t defaultConvertFunc(std::string input) { return 0; }

public:
    std::string mDefaultBindings; ///< Default Bindings as a std::string, used if no file is found
};

#endif // _BINDINGS_H
}}
