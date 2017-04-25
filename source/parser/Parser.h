#include "ParserNode.h"
#include <string>
#include <vector>

namespace liquid { namespace parser {
#ifndef _PARSER_H
#define _PARSER_H

/** \class Parser
 *
 * \ingroup Data
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

    /** \brief Gets the ParserNode with the given name
      * \param name Name of the ParserNode represented as a std::string
      * \return Gets the found ParserNode, nullptr if not found
      */
    ParserNode* getParserNode(std::string name);

    std::list<ParserNode*> getParserNodes(std::string name);

    /// \return Gets the Root ParserNode for this Parser
    ParserNode* getRootParserNode();

protected:
    ParserNode* findParserNodeByName(std::string name, ParserNode* node);
    void findParserNodes(std::string name, ParserNode* node, std::list<ParserNode*>& nodes);

protected:
    ParserNode* mRootParserNode; ///< Root ParserNode for the Parser Tree
};

#endif // _PARSER_H
}}
