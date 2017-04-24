#include "Parser.h"

namespace liquid {
namespace data {

    Parser::Parser()
    {
    }

    Parser::~Parser()
    {}

    void Parser::parseFile(std::string file)
    {

    }

    void Parser::parseString(std::string str)
    {

    }

    ParserNode* Parser::getParserNode(std::string name) const
    {
        for (uint32_t i = 0; i < mParserNodes.size(); i++)
        {
            if (mParserNodes[i]->getName() == name)
                return mParserNodes[i];
        }

        return nullptr;
    }

    ParserNode* Parser::getParserNode(int32_t index) const
    {
        if (index >= 0 && index < mParserNodes.size())
            return mParserNodes[index];

        return nullptr;
    }

    const int32_t Parser::getParseNodeCount() const
    {
        return mParserNodes.size();
    }

    const std::vector<ParserNode*>& Parser::getParserNodes() const
    {
        return mParserNodes;
    }

}}
