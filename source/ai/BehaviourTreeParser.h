#include "BehaviourNode.h"
#include "nodes/LeafNode.h"
#include "nodes/RepeaterNode.h"
#include "nodes/SequenceNode.h"
#include "../parser/ParserXML.h"
#include "../parser/ParserNodeSearch.h"

namespace liquid { namespace ai {
#ifndef _BEHAVIOURTREEPARSER_H
#define _BEHAVIOURTREEPARSER_H

class BehaviourTreeParser
{
public:
    BehaviourTreeParser(parser::Parser& parser);
    ~BehaviourTreeParser();

    BehaviourNode* getConstructedNode();

    void findNextNode(BehaviourNode* bNode, parser::ParserNode* pNode);

protected:
    BehaviourNode* mConstructedNode;
};

#endif // _BEHAVIOURTREEPARSER_H
}}
