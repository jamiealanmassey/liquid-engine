#include "ParticleData.h"

namespace liquid {
namespace data {

    ParticleData::ParticleData(ConfigurationParser parser)
    {
        // TODO: Remove this hardcode
        std::string defaultParticle =
            "velocityX 0.05\n"
            "velocityXMin -0.4\n"
            "velocityXMax 0.2\n"
            "velocityXTarget 0.1\n"
            "\n"
            "velocityY 0.05\n"
            "velocityYMin -0.4\n"
            "velocityYMax 0.2\n"
            "velocityYTarget 0.1\n"
            "\n"
            "colourR 100.0\n"
            "colourRMin 0.0\n"
            "colourRMax 0.0\n"
            "colourRTarget 255.0\n"
            "\n"
            "colourG 100.0\n"
            "colourGMin 0.0\n"
            "colourGMax 0.0\n"
            "colourGTarget 255.0\n"
            "\n"
            "colourB 100.0\n"
            "colourBMin 0.0\n"
            "colourBMax 0.0\n"
            "colourBTarget 255.0\n"
            "\n"
            "colourA 255.0\n"
            "colourAMin 0.0\n"
            "colourAMax 0.0\n"
            "colourATarget 0.0\n"
            "\n"
            "lifespan 2000.0\n"
            "lifespanMin 0.0\n"
            "lifespanMax 0.0\n"
            "\n";

        parser.parseString(defaultParticle);

        mVelocityX[PARTICLE_VALUE] = parser.getValueAsFloat("velocityX");
        mVelocityX[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("velocityXMin");
        mVelocityX[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("velocityXMax");
        mVelocityX[PARTICLE_TARGET_VALUE] = parser.getValueAsFloat("velocityXTarget");

        mVelocityY[PARTICLE_VALUE] = parser.getValueAsFloat("velocityY");
        mVelocityY[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("velocityYMin");
        mVelocityY[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("velocityYMax");
        mVelocityY[PARTICLE_TARGET_VALUE] = parser.getValueAsFloat("velocityYTarget");

        mColourR[PARTICLE_VALUE] = parser.getValueAsFloat("colourR");
        mColourR[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("colourRMin");
        mColourR[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("colourRMax");
        mColourR[PARTICLE_TARGET_VALUE] = parser.getValueAsFloat("colourRTarget");

        mColourG[PARTICLE_VALUE] = parser.getValueAsFloat("colourG");
        mColourG[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("colourGMin");
        mColourG[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("colourGMax");
        mColourG[PARTICLE_TARGET_VALUE] = parser.getValueAsFloat("colourGTarget");

        mColourB[PARTICLE_VALUE] = parser.getValueAsFloat("colourB");
        mColourB[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("colourBMin");
        mColourB[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("colourBMax");
        mColourB[PARTICLE_TARGET_VALUE] = parser.getValueAsFloat("colourBTarget");

        mColourA[PARTICLE_VALUE] = parser.getValueAsFloat("colourA");
        mColourA[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("colourAMin");
        mColourA[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("colourAMax");
        mColourA[PARTICLE_TARGET_VALUE] = parser.getValueAsFloat("colourATarget");

        mSizeX[PARTICLE_VALUE] = parser.getValueAsFloat("sizeX");
        mSizeX[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("sizeXMin");
        mSizeX[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("sizeXMax");
        mSizeX[PARTICLE_TARGET_VALUE] = parser.getValueAsFloat("sizeXTarget");

        mSizeY[PARTICLE_VALUE] = parser.getValueAsFloat("sizeY");
        mSizeY[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("sizeYMin");
        mSizeY[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("sizeYMax");
        mSizeY[PARTICLE_TARGET_VALUE] = parser.getValueAsFloat("sizeYTarget");

        mLifeSpan[PARTICLE_VALUE] = parser.getValueAsFloat("lifespan");
        mLifeSpan[PARTICLE_VARIANCE_MIN] = parser.getValueAsFloat("lifespanMin");
        mLifeSpan[PARTICLE_VARIANCE_MAX] = parser.getValueAsFloat("lifespanMax");

        mTexture = parser.getValueAsString("texture");
        mEaseFunction = parser.getValueAsString("easingFunc");
    }
    
    ParticleData::~ParticleData()
    {}

    const ParticleData::ParticleData::ParticleNode ParticleData::ParticleData::getVelocityX() const
    {
        return mVelocityX;
    }

    const ParticleData::ParticleNode ParticleData::getVelocityY() const
    {
        return mVelocityY;
    }

    const ParticleData::ParticleNode ParticleData::getColourR() const
    {
        return mColourR;
    }

    const ParticleData::ParticleNode ParticleData::getColourG() const
    {
        return mColourG;
    }

    const ParticleData::ParticleNode ParticleData::getColourB() const
    {
        return mColourB;
    }

    const ParticleData::ParticleNode ParticleData::getColourA() const
    {
        return mColourA;
    }

    const ParticleData::ParticleNode ParticleData::getSizeX() const
    {
        return mSizeX;
    }

    const ParticleData::ParticleNode ParticleData::getSizeY() const
    {
        return mSizeY;
    }

    const ParticleData::ParticleNode ParticleData::getLifeSpan() const
    {
        return mLifeSpan;
    }

    const std::string ParticleData::getTexture() const
    {
        return mTexture;
    }

    const std::string ParticleData::getEasingFunctionName() const
    {
        return mEaseFunction;
    }

}}