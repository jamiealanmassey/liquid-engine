#include "nodes/base/BehaviourNode.h"
#include "nodes/base/LeafNode.h"
#include "nodes/impl/RepeaterNode.h"
#include "nodes/impl/SequenceNode.h"
#include "../parser/ParserXML.h"
#include "../parser/ParserNodeSearch.h"

namespace liquid { namespace ai {
#ifndef _BEHAVIOURTREEPARSER_H
#define _BEHAVIOURTREEPARSER_H

/**
 * \class BehaviourTreeParser
 *
 * \ingroup AI
 * \brief Describes how to load and generate BehaviourNode data from the specified parser::Parser
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class BehaviourTreeParser
{
public:
    /** \brief BehaviourTreeParser Constructor
      * \param parser Pre-loaded parser::Parser object
      */
    BehaviourTreeParser(parser::Parser& parser);

    /// BehaviourTreeParser Destructor
    ~BehaviourTreeParser();

    /** \brief Constructs the BehaviourTree data where mConstructedNode is the origin
      * \return Constructed tree with this as the root node, give this node to the BehaviourTree class
      */
    BehaviourNode* getConstructedNode();

    /** \brief Recursively parse the next parser::ParserNode constructing a BehaviourNode
      * \param bNode Last BehaviourNode to be created
      * \param pNode Next parser::ParserNode to be parsed
      */
    void findNextNode(BehaviourNode* bNode, parser::ParserNode* pNode);

protected:
    BehaviourNode* mConstructedNode; ///< Fully constructed BehaviourNode with children as a tree
};

#endif // _BEHAVIOURTREEPARSER_H
}}
