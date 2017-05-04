#include <vector>
#include <algorithm>

namespace liquid { namespace ai {
#ifndef _BEHAVIOURNODE_H
#define _BEHAVIOURNODE_H

/**
 * \class BehaviourNode
 *
 * \ingroup AI
 * \brief Simple extensible interface class for any type of Behaviour Tree node
 *
 * \author Jamie Massey
 * \version 1.1
 * \date 04/05/2017
 *
 */

class BehaviourNode
{
public:
    /// Defines the type of the BehaviourNode (leaf, composite or decorator)
    enum eNodeType
    {
        NODETYPE_LEAF = 0,
        NODETYPE_COMPOSITE = 1,
        NODETYPE_DECORATOR = 2,
    };

public:
    /** \brief BehaviourNode Constructor
      * \param type Type of the BehaviourNode 
      */
    BehaviourNode(eNodeType type);
    
    /// BehaviourNode Destructor
    ~BehaviourNode();

    /// \brief Virtual function called when node is reset/started
    virtual void initialise();

    /** \brief Pure virtual function to be called when evaluating the tree
      * \return When true is returned the process was successful, otherwise it failed
      */
    virtual bool process() = 0;

    /** \brief Pure virtual that adds a child BehaviourNode to this node
      * \param node Pointer to the node to be added
      */
    virtual void insertChild(BehaviourNode* node) = 0;

    /** \brief Pure virtual that removes a child BehaviourNode from this node
      * \param node Pointer to the node to be removed
      */
    virtual void removeChild(BehaviourNode* node) = 0;

    /// \return Gets the type of this BehaviourNode (leaf, composite or decorator)
    const eNodeType getNodeType() const;

    /// \return Gets the children of this node as a collection
    std::vector<BehaviourNode*> getChildren() const;

    /// \return Gets the children of this node in a shuffled order as a collection
    std::vector<BehaviourNode*> getChildrenShuffled() const;

protected:
    eNodeType                   mNodeType; ///< Denotes the type of this BehaviourNode
    std::vector<BehaviourNode*> mChildren; ///< Collection of child BehaviourNode objects
};

#endif // _BEHAVIOURNODE_H
}}
