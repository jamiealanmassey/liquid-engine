#include "ParticleData.h"

namespace liquid {
namespace data {

    ParticleData::ParticleData(parser::Parser parser)
    {
        parser::ParserNode* node = parser.getParserNode(0);

        mVelocityX[PARTICLE_VALUE] = node->getValueAsFloat("velocityXValue");
        mVelocityX[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("velocityXMin");
        mVelocityX[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("velocityXMax");
        mVelocityX[PARTICLE_TARGET_VALUE] = node->getValueAsFloat("velocityXTarget");

        mVelocityY[PARTICLE_VALUE] = node->getValueAsFloat("velocityYValue");
        mVelocityY[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("velocityYMin");
        mVelocityY[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("velocityYMax");
        mVelocityY[PARTICLE_TARGET_VALUE] = node->getValueAsFloat("velocityYTarget");

        mColourR[PARTICLE_VALUE] = node->getValueAsFloat("colourRValue");
        mColourR[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("colourRMin");
        mColourR[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("colourRMax");
        mColourR[PARTICLE_TARGET_VALUE] = node->getValueAsFloat("colourRTarget");

        mColourG[PARTICLE_VALUE] = node->getValueAsFloat("colourGValue");
        mColourG[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("colourGMin");
        mColourG[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("colourGMax");
        mColourG[PARTICLE_TARGET_VALUE] = node->getValueAsFloat("colourGTarget");

        mColourB[PARTICLE_VALUE] = node->getValueAsFloat("colourBValue");
        mColourB[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("colourBMin");
        mColourB[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("colourBMax");
        mColourB[PARTICLE_TARGET_VALUE] = node->getValueAsFloat("colourBTarget");

        mColourA[PARTICLE_VALUE] = node->getValueAsFloat("colourAValue");
        mColourA[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("colourAMin");
        mColourA[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("colourAMax");
        mColourA[PARTICLE_TARGET_VALUE] = node->getValueAsFloat("colourATarget");

        mSizeX[PARTICLE_VALUE] = node->getValueAsFloat("sizeXValue");
        mSizeX[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("sizeXMin");
        mSizeX[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("sizeXMax");
        mSizeX[PARTICLE_TARGET_VALUE] = node->getValueAsFloat("sizeXTarget");

        mSizeY[PARTICLE_VALUE] = node->getValueAsFloat("sizeYValue");
        mSizeY[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("sizeYMin");
        mSizeY[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("sizeYMax");
        mSizeY[PARTICLE_TARGET_VALUE] = node->getValueAsFloat("sizeYTarget");

        mLifeSpan[PARTICLE_VALUE] = node->getValueAsFloat("lifespanValue");
        mLifeSpan[PARTICLE_VARIANCE_MIN] = node->getValueAsFloat("lifespanMin");
        mLifeSpan[PARTICLE_VARIANCE_MAX] = node->getValueAsFloat("lifespanMax");

        mTexture = node->getValueAsString("texture");
        mEaseFunction = node->getValueAsString("easingFunc");
    }
    
    ParticleData::~ParticleData()
    {}

    const ParticleData::ParticleNode ParticleData::ParticleData::getVelocityX() const
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

    const std::string ParticleData::mDefaultParticle =
        "velocityXValue 0.0\n"
        "velocityXMin -0.5\n"
        "velocityXMax 0.5\n"
        "velocityXTarget 0.0\n"
        "\n"
        "velocityYValue 0.0\n"
        "velocityYMin -0.5\n"
        "velocityYMax 0.5\n"
        "velocityYTarget 0.0\n"
        "\n"
        "colourRValue 50.0\n"
        "colourRMin 0.0\n"
        "colourRMax 0.0\n"
        "colourRTarget 255.0\n"
        "\n"
        "colourGValue 255.0\n"
        "colourGMin 0.0\n"
        "colourGMax 0.0\n"
        "colourGTarget 50.0\n"
        "\n"
        "colourBValue 50.0\n"
        "colourBMin 0.0\n"
        "colourBMax 0.0\n"
        "colourBTarget 255.0\n"
        "\n"
        "colourAValue 255.0\n"
        "colourAMin 0.0\n"
        "colourAMax 0.0\n"
        "colourATarget 0.0\n"
        "\n"
        "lifespanValue 1500.0\n"
        "lifespanMin 0.0\n"
        "lifespanMax 0.0\n";

    const std::string ParticleData::mDefaultParticleXML =
        "<particle name = \"particle\">\n"
        "<attribute name = \"velocityX\">\n"
        "<data name = \"velocityXValue\">0.0</data>\n"
        "<data name = \"velocityXMin\">-0.5</data>\n"
        "<data name = \"velocityXMax\">0.5</data>\n"
        "<data name = \"velocityXTarget\">0.0</data>\n"
        "</attribute>\n"
        "<attribute name = \"velocityY\">\n"
        "<data name = \"velocityYValue\">0.0</data>\n"
        "<data name = \"velocityYMin\">-0.5</data>\n"
        "<data name = \"velocityYMax\">0.5</data>\n"
        "<data name = \"velocityYTarget\">0.0</data>\n"
        "</attribute>\n"
        "<attribute name = \"colourR\">\n"
        "<data name = \"colourRValue\">50.0</data>\n"
        "<data name = \"colourRMin\">0.0</data>\n"
        "<data name = \"colourRMax\">0.0</data>\n"
        "<data name = \"colourRTarget\">255.0</data>\n"
        "</attribute>\n"
        "<attribute name = \"colourG\">\n"
        "<data name = \"colourGValue\">255.0</data>\n"
        "<data name = \"colourGMin\">0.0</data>\n"
        "<data name = \"colourGMax\">0.0</data>\n"
        "<data name = \"colourGTarget\">50.0</data>\n"
        "</attribute>\n"
        "<attribute name = \"colourB\">\n"
        "<data name = \"colourBValue\">50.0</data>\n"
        "<data name = \"colourBMin\">0.0</data>\n"
        "<data name = \"colourBMax\">0.0</data>\n"
        "<data name = \"colourBTarget\">255.0</data>\n"
        "</attribute>\n"
        "<attribute name = \"colourA\">\n"
        "<data name = \"colourAValue\">255.0</data>\n"
        "<data name = \"colourAMin\">0.0</data>\n"
        "<data name = \"colourAMax\">0.0</data>\n"
        "<data name = \"colourATarget\">0.0</data>\n"
        "</attribute>\n"
        "<attribute name = \"lifespan\">\n"
        "<data name = \"lifespanValue\">1500.0</data>\n"
        "<data name = \"lifespanMin\">0.0</data>\n"
        "<data name = \"lifespanMax\">0.0</data>\n"
        "</attribute>\n"
        "</particle>\n";

}}
