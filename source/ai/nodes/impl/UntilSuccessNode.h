#include "../base/DecoratorNode.h"

namespace liquid { namespace ai {
#ifndef _UNTILSUCCESSNODE_H
#define _UNTILSUCCESSNODE_H

/**
* \class UntilSuccessNode
*
* \ingroup AI
* \brief Keeps processing until the child node returns success
*
* \author Jamie Massey
* \version 1.0
* \date 04/05/2017
*
*/

class UntilSuccessNode : public DecoratorNode
{
public:
    /// UntilSuccessNode Constructor
    UntilSuccessNode();

    /// UntilSuccessNode Destructor
    ~UntilSuccessNode();

    /// \brief Overload BehaviourNode::process, processes until the child succeeds
    virtual bool process() override;
};

#endif // _UNTILSUCCESSNODE_H
}}
