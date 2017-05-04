#include "BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _COMPOSITENODE_H
#define _COMPOSITENODE_H

/**
 * \class CompositeNode
 *
 * \ingroup AI
 * \brief A BehaviourNode that has one or more children and processes them in different ways
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class CompositeNode : public BehaviourNode
{
public:
    /// CompositeNode Constructor
    CompositeNode();

    /// CompositeNode Destructor
    ~CompositeNode();

    /** \brief Adds a child BehaviourNode to this node
      * \param node Pointer to the node to be added
      */
    virtual void insertChild(BehaviourNode* node) override;

    /** \brief Removes a child BehaviourNode from this node
      * \param node Pointer to the node to be removed
      */
    virtual void removeChild(BehaviourNode* node) override;
};

#endif // _COMPOSITENODE_H
}}
