#include "BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _LEAFNODE_H
#define _LEAFNODE_H

/**
 * \class LeafNode
 *
 * \ingroup AI
 * \brief Incapable of a child, performs game specific operations
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class LeafNode : public BehaviourNode
{
public:
    /// LeafNode Constructor
    LeafNode();

    /// LeafNode Destructor
    ~LeafNode();

    /** \brief Adds a child BehaviourNode to this node
      * \param node Pointer to the node to be added
      */
    virtual void insertChild(BehaviourNode* node) override;

    /** \brief Removes a child BehaviourNode from this node
      * \param node Pointer to the node to be removed
      */
    virtual void removeChild(BehaviourNode* node) override;
};

#endif // _LEAFNODE_H
}}
