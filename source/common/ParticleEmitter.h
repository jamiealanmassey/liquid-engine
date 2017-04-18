#include "Entity.h"

namespace liquid { namespace common {
#ifndef _PARTICLEEMITTER_H
#define _PARTICLEEMITTER_H

/**
 * \class ParticleEmitter
 *
 * \ingroup Common
 * \brief Subsystem that manages a Particle System for simulating
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 18/04/2017
 *
 */

class ParticleEmitter : public Entity
{
public:
    ParticleEmitter();
    ~ParticleEmitter();
};

#endif // _PARTICLEEMITTER_H
}}
