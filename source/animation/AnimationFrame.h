#include "../data/TextureAtlas.h"
#include <array>

namespace liquid { namespace animation {
#ifndef _ANIMATIONFRAME_H
#define _ANIMATIONFRAME_H

class AnimationFrame
{
public:
    AnimationFrame(data::TextureAtlas& atlas, std::string atlasName, float frameDelay);
    AnimationFrame(std::array<float, 2> texCoord1, std::array<float, 2> texCoord2, 
                   std::array<float, 2> texCoord3, std::array<float, 2> texCoord4,
                   float frameDelay);

    ~AnimationFrame();

    const std::array<float, 2> getTexCoord1() const;
    const std::array<float, 2> getTexCoord2() const;
    const std::array<float, 2> getTexCoord3() const;
    const std::array<float, 2> getTexCoord4() const;
    const float getFrameDelay() const;

protected:
    std::array<float, 2> mTexCoord1;
    std::array<float, 2> mTexCoord2;
    std::array<float, 2> mTexCoord3;
    std::array<float, 2> mTexCoord4;
    float                mFrameDelay;
};

#endif // _ANIMATIONFRAME_H
}}
