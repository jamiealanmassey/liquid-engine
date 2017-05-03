#include "SteeringBehaviour.h"

namespace liquid { namespace ai {
#ifndef _SEEK_H
#define _SEEK_H

class Seek : public SteeringBehaviour
{
public:
    Seek();
    ~Seek();

    shape::Vector2& getSteeringForce(Agent& agent) override;
};

#endif // _SEEK_H
}}
