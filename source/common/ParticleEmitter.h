#include "Entity.h"
#include "Particle.h"
#include "Layer.h"
#include "../data/ParticleData.h"
#include "../graphics/RenderableBatch.h"

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
    /// The type of this emitter: undef, directional or circular
    enum eEmitterType
    {
        EMITTERTYPE_UNDEFINED = 0,
        EMITTERTYPE_DIRECTIONAL = 1,
        EMITTERTYPE_CIRCULAR = 2,
    };

public:
    /** \brief ParticleEmitter Constructor
      * \param particleData Reference to the intended particle data to construct Particle objects
      * \param batch Pointer to the graphics::BatchRenderable to use for drawing
      * \param count Number of Particles to emit
      */
    ParticleEmitter(data::ParticleData& particleData, Layer* layerPtr, uint32_t count);
   
    /// ParticleEmitter Destructor
    ~ParticleEmitter();

    /** \brief Called every frame
      *
      * Used to update active Particles and emit new ones when required, if the
      * emitter is continuous it will keep respawning Particle objects using
      * Particle::emit(float x, float y) and the mBirthRate variable to control
      * how often they will spawn.
      */
    virtual void update() override;

    /// \brief Updates Post normal ParticleEmitter::update function
    virtual void updatePost() override;

    /** \brief Overrides the usual Entity::setPosition(float x, float y) function
      * \param x X-Axis position of the emitter
      * \param y Y-Axis position of the emitter
      *
      * When called this function will also update the position of all child
      * Particle objects that have been emitted and not.
      */
    virtual void setPosition(float x, float y) override;

    /** \brief Overrides the usual Entity::addPosition(float x, float y) function
      * \param x X-Axis position to add to the emitter
      * \param y Y-Axis position to add to the emitter
      *
      * When called this function will also update the position of all child
      * Particle objects that have been emitted and not.
      */
    virtual void addPosition(float x, float y) override;

    void emit();

    /** \brief Controls the rate at which new Particle objects are emitted
      * \param rate Float representation of birth rate in milliseconds
      */
    void setBirthRate(float rate);

    /** \brief Controls wether the emitter repeats constantly or emits just once
      * \param flag Flag to assign
      */
    void setRepeat(bool flag) { mRepeat = flag; }

    /** \brief Updates the type of this emitter
      * \param type Emitter type to set this object to
      */
    void setType(eEmitterType type);

    /// Gets the Particle Count of this emitter
    const uint32_t getParticlesCount() const;

    /// Gets the Rate at which the emitter births Particle objects
    const float getBirthRate() const;

    /// Gets the total accumulated birth time for the next Particle
    const float getBirthAccumulator() const;

    /// Gets the type of this ParticleEmitter
    const eEmitterType getType() const;

    /// Gets a referenced list to the collection of Particle objects stored
    const std::vector<Particle*>& getParticles();

protected:
    uint32_t               mParticlesBirth;   ///< Number of particles to birth
    uint32_t               mParticlesCount;   ///< Number of particles stored in this emitter
    float                  mBirthRate;        ///< Rate at which to birth new particles in milliseconds
    float                  mBirthAccumulator; ///<  Accumulates for birthing new Particles
    bool                   mRepeat;           ///< Denotes if the emitter should repeat
    eEmitterType           mType;             ///< Stored type of this emitter
    std::vector<Particle*> mParticles;        ///< Collection of Particle objects for use by this emitter

protected:
    graphics::RenderableBatch* mRenderableBatch; ///< Pointer to the graphics::RenderableBatch to draw with
    data::ParticleData&        mParticleData;    ///< Reference to the ParticleData (i.e. a template for birthing particles)
};

#endif // _PARTICLEEMITTER_H
}}
