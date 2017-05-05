#include "nodes/base/BehaviourNode.h"
#include "BehaviourContext.h"

namespace liquid { namespace ai {
#ifndef _BEHAVIOURTREE_H
#define _BEHAVIOURTREE_H

/**
 * \class BehaviourTree
 *
 * \ingroup AI
 * \brief Stores a tree using a root BehaviourNode and a reference to the node currently being processed
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class BehaviourTree /*: public BehaviourNode*/
{
public:
    /// BehaviourTree Constructor
    BehaviourTree();

    /// BehaviourTree Destructor
    ~BehaviourTree();

    /// Overrides BehaviourNode::initialise
    //virtual void initialise() override;

    /// Overrides BehaviourNode::process, uses mNodeCurrent to process accordingly
    //virtual bool process() override;
    
    bool process();

    /// \return Returns mNodeCurrent
    virtual BehaviourNode* nextNode();

    /** \brief Assigns the root node of this tree
      * \param node Node to be assigned as the root
      *
      * When assigned the function will search through to the bottom of the
      * tree and also assign mNodeCurrent to that node so that when it is processed
      * the object can works its way back up in a structured way to mNodeRoot
      */
    void setNodeRoot(BehaviourNode* node);

    /// \return Pointer to the root BehaviourNode of the tree
    BehaviourNode* getNodeRoot();

    /// \return Pointer to the context for this BehaviourTree
    BehaviourContext* getContext();

    /// \return Pointer to the current BehaviourNode that the tree is processing
    //BehaviourNode* getNodeCurrent();

protected:
    BehaviourNode*    mRootNode; ///< Root node of the BehaviourTree
    BehaviourContext* mContext;  ///< Context for the data stored for this tree
    //BehaviourNode* mNodeCurrent; ///< Node that is currently being processed by the tree
};

#endif // _BEHAVIOURTREE_H
}}
