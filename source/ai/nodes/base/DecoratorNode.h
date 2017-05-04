#include "BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _DECORATORNODE_H
#define _DECORATORNODE_H

/**
 * \class DecoratorNode
 *
 * \ingroup AI
 * \brief Limited to one child node, either transform the result, terminate or repeat the process
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class DecoratorNode : public BehaviourNode
{
public:
    /// DecoratorNode Constructor
    DecoratorNode();

    /// DecoratorNode Destructor
    ~DecoratorNode();

    /** \brief Adds a child BehaviourNode to this node
      * \param node Pointer to the node to be added
      */
    virtual void insertChild(BehaviourNode* node) override;

    /** \brief Removes a child BehaviourNode from this node
      * \param node Pointer to the node to be removed
      */
    virtual void removeChild(BehaviourNode* node) override;
};

#endif // _DECORATORNODE_H
}}
