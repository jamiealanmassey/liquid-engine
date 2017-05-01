#include "../BehaviourNode.h"
#include <functional>

namespace liquid { namespace ai {
#ifndef _LEAFNODE_H
#define _LEAFNODE_H

/**
 * \class LeafNode
 *
 * \ingroup AI
 * \brief Checks for some kind of objective to be satisfied and calls game-related functions
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class LeafNode : public BehaviourNode
{
public:
    /// Defines callback for Behaviour-oriented functions
    typedef std::function<uint32_t()> BehaviourFunc;

public:
    /// LeafNode Constructor
    LeafNode();

    /// LeafNode Destructor
    ~LeafNode();

    /// Overrides BehaviourNode::initialise
    virtual void initialise() override;

    /// Overrides BehaviourNode::process
    virtual void process() override;

    /** \brief Overrides BehaviourNode::insertChild to stop children from being added
      * \param node Child node to be inserted
      */
    virtual void insertChild(BehaviourNode* node) override;

    /** \brief Overrides BehaviourNode::insertChild to stop children being removed
      * \param node Child node to be inserted
      */
    virtual void removeChild(BehaviourNode* node) override;

    /** \brief Override BehaviourNode::nextNode to return nullptr
      * \return Always returns nullptr, LeafNode objects should have no children
      */
    virtual BehaviourNode* nextNode() override;

    /** \brief Assigns the mFuncInitialise Callback
      * \param func Function to assign
      */
    void setFuncInitialise(BehaviourFunc func);

    /** \brief Assigns the mFuncProcess Callback
      * \param func Function to assign
      */
    void setFuncProcess(BehaviourFunc func);

protected:
    BehaviourFunc mFuncInitialise; ///< Function callback triggered when initialise() is called
    BehaviourFunc mFuncProcess;    ///< Function callback triggered when process() is called, returning value updates mNodeState (0, 1, 2)
};

#endif // _LEAFNODE_H
}}
