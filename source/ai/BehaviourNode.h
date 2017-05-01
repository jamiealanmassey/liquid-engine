#include <vector>
#include <algorithm>

namespace liquid { namespace ai {
#ifndef _BEHAVIOURNODE_H
#define _BEHAVIOURNODE_H

/**
 * \class BehaviourNode
 *
 * \ingroup AI
 * \brief Base class with some virtual functions that describes the general structure of any BehaviourNode in the tree
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class BehaviourNode
{
public:
    /// Defines the states that the BehaviourNode can be in: processing, successful or failure
    enum eBehaviourNodeState
    {
        NODESTATE_PROCESSING = 0,
        NODESTATE_SUCCESSFUL = 1,
        NODESTATE_FAILURE = 2,
    };

    /** \brief Defines the type of the BehaviourNode
      *
      * Composite: One or more children, different processing methods\n
      * Decorator: Limited to one child node, either transform the result, terminate or repeat the process\n
      * Leaf: Incapable of a child, performs game specific operations
      */
    enum eBehaviourNodeType
    {
        NODETYPE_COMPOSITE = 0,
        NODETYPE_DECORATOR = 1,
        NODETYPE_LEAF = 2,
    };

public:
    /// BehaviourNode Constructor
    BehaviourNode();

    /// BehaviourNode Destructor
    ~BehaviourNode();

    /// \brief Pure virtual function called to start/reset the node
    virtual void initialise() = 0;

    /// \brief Pure virtual function used to process the node and change mNodeState
    virtual void process() = 0;

    /** \brief Inserts a new child node into mChildren
      * \param node Node to be inserted
      */
    virtual void insertChild(BehaviourNode* node);

    /** \brief Removes a child node from mChildren
      * \param node Node to be removed
      */
    virtual void removeChild(BehaviourNode* node);

    /** \brief Gets the next node from mChildren
      * \return Default: first child, nullptr if no children
      */
    virtual BehaviourNode* nextNode();

    /** \brief Assign this node's parent node
      * \param node Parent node to assign
      */
    void setParentNode(BehaviourNode* node);

    /// \return Gets this node's current eBehaviourNodeState
    const eBehaviourNodeState getNodeState() const;

    /// \return Gets the node's eBehaviourNodeType
    const eBehaviourNodeType getNodeType() const;

    /// \return Parent of this node, nullptr if no parent
    BehaviourNode* getParentNode();

    /// \return Collection of children BehaviourNode objects
    std::vector<BehaviourNode*> getChildren();

protected:
    eBehaviourNodeState         mNodeState;  ///< Current state of the node: processing, successful or failure
    eBehaviourNodeType          mNodeType;   ///< Type of this node: composite, decorator or leaf
    BehaviourNode*              mParentNode; ///< Parent node of this node
    std::vector<BehaviourNode*> mChildren;   ///< Collection of children BehaviourNode objects
};

#endif // _BEHAVIOURNODE_H
}}
