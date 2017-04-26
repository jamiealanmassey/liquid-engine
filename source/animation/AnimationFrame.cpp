#include "AnimationFrame.h"

namespace liquid {
namespace animation {

    AnimationFrame::AnimationFrame(data::TextureAtlas& atlas, std::string atlasName, float frameDelay)
    {
        data::TextureAtlas::TextureRegion region = atlas.getTextureRegion(atlasName);
        mTexCoord1 = region[0];
        mTexCoord1 = region[1];
        mTexCoord1 = region[2];
        mTexCoord1 = region[3];
        mFrameDelay = frameDelay;
    }

    AnimationFrame::AnimationFrame(std::array<float, 2> texCoord1, std::array<float, 2> texCoord2,
                                   std::array<float, 2> texCoord3, std::array<float, 2> texCoord4,
                                   float frameDelay)
    {
        mTexCoord1 = texCoord1;
        mTexCoord2 = texCoord2;
        mTexCoord3 = texCoord3;
        mTexCoord4 = texCoord4;
        mFrameDelay = frameDelay;
    }

    AnimationFrame::~AnimationFrame()
    {}

    const std::array<float, 2> AnimationFrame::getTexCoord1() const
    {
        return mTexCoord1;
    }

    const std::array<float, 2> AnimationFrame::getTexCoord2() const
    {
        return mTexCoord2;
    }

    const std::array<float, 2> AnimationFrame::getTexCoord3() const
    {
        return mTexCoord3;
    }
    const std::array<float, 2> AnimationFrame::getTexCoord4() const
    {
        return mTexCoord4;
    }

    const float AnimationFrame::getFrameDelay() const
    {
        return mFrameDelay;
    }

}}
