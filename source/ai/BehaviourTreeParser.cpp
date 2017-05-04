#include "BehaviourTreeParser.h"

namespace liquid {
namespace ai {

    BehaviourTreeParser::BehaviourTreeParser(parser::Parser& parser)
    {
        findNextNode(nullptr, parser.getRootParserNode());
    }
    
    BehaviourTreeParser::~BehaviourTreeParser()
    {
    }

    BehaviourNode* BehaviourTreeParser::getConstructedNode()
    {
        return mConstructedNode;
    }

    void BehaviourTreeParser::findNextNode(BehaviourNode* bNode, parser::ParserNode* pNode)
    {
        parser::ParserNodeSearch search(pNode);
        parser::ParserNode* typeNode = search.findParserNodesRelative("type").front();
        BehaviourNode* nextNode = nullptr;

        if (typeNode != nullptr)
        {
            std::string type = typeNode->getValueAsString("type");
            std::list<parser::ParserNode*> nodes = search.findParserNodesRelative("node");

            if (type == "RepeaterNode")
            {
                nextNode = new RepeaterNode;
                parser::ParserNode* limitNode = search.findParserNodesRelative("limit").front();
                static_cast<RepeaterNode*>(nextNode)->setRepeaterLimit(limitNode->getValueAsInteger32("limit"));
            }
            else if (type == "SequenceNode")
                nextNode = new SequenceNode;

            if (bNode != nullptr)
                bNode->insertChild(nextNode);
            else
                mConstructedNode = nextNode;

            for (auto foundNode : nodes)
                findNextNode(nextNode, foundNode);
        }
    }

}}
