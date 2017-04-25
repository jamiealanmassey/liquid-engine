#include "ParserNode.h"
#include <string>
#include <vector>

namespace liquid { namespace parser {
#ifndef _PARSER_H
#define _PARSER_H

/** \class Parser
 *
 * \ingroup Parser
 * \brief Uses the ParserNode class to store and parse a collection of linked ParserNode objects as a tree
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 24/04/2017
 *
 */

class Parser
{
public:
    /// Parser Constructor
    Parser();

    /// Parser Destructor
    ~Parser();

    /** \brief Virtual function for parsing files
      * \brief file Path to the file for parsing
      */
    virtual void parseFile(std::string file);

    /** \brief Virtual function for parsing from a string
      * \brief str String to be parsed
      */
    virtual void parseString(std::string str);

    /// \return Gets the Root ParserNode for this Parser
    ParserNode* getRootParserNode();

protected:
    ParserNode* mRootParserNode; ///< Root ParserNode for the Parser Tree
};

#endif // _PARSER_H
}}
