#include "Parser.h"

namespace liquid {
namespace parser {

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

    ParserNode* Parser::getParserNode(std::string name)
    {
        return findParserNodeByName(name, mRootParserNode);
    }

    std::list<ParserNode*> Parser::getParserNodes(std::string name)
    {
        std::list<ParserNode*> nodes;
        findParserNodes(name, mRootParserNode, nodes);
        return nodes;
    }

    ParserNode* Parser::getRootParserNode()
    {
        return mRootParserNode;
    }

    ParserNode* Parser::findParserNodeByName(std::string name, ParserNode* node)
    {
        if (node->getName() == name)
            return node;

        std::list<ParserNode*> children = node->getChildren();
        ParserNode* nodeSearch = nullptr;

        for (auto child : children)
        {
            nodeSearch = findParserNodeByName(name, child);

            if (nodeSearch != nullptr)
                return nodeSearch;
        }

        return nullptr;
    }

    void Parser::findParserNodes(std::string name, ParserNode* node, std::list<ParserNode*>& nodes)
    {
        if (node->getName() == name)
            nodes.push_back(node);

        for (auto child : node->getChildren())
            findParserNodes(name, child, nodes);
    }

}}
