#include "ParserNode.h"
#include <string>
#include <vector>

namespace liquid { namespace data {
#ifndef _PARSER_H
#define _PARSER_H

/** \class Parser
 *
 * \ingroup Data
 * \brief Uses the ParserNode class to store and parse a linked-list of data
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 24/04/2017
 *
 */

class Parser
{
public:
    Parser();
    ~Parser();

    virtual void parseFile(std::string file);
    virtual void parseString(std::string str);

    ParserNode* getParserNode(std::string name) const;
    ParserNode* getParserNode(int32_t index) const;

    const int32_t getParseNodeCount() const;
    const std::vector<ParserNode*>& getParserNodes() const;

protected:
    std::vector<ParserNode*> mParserNodes; ///< 
};

#endif // _PARSER_H
}}
