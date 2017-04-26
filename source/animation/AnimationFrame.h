#include "../data/TextureAtlas.h"
#include <array>

namespace liquid { namespace animation {
#ifndef _ANIMATIONFRAME_H
#define _ANIMATIONFRAME_H

/**
 * \class AnimationFrame
 *
 * \ingroup Animation
 * \brief Describes a single frame in a whole Animation
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 26/04/2017
 *
 */

class AnimationFrame
{
public:
    /** \brief AnimationFrame Constructor
      * \param atlas Reference to the data::TextureAtlas to use find texture coordinate
      * \param atlasName Name of the texture region in the given atlas
      * \param frameDelay Delay in milliseconds between this frame and the next
      */
    AnimationFrame(data::TextureAtlas& atlas, std::string atlasName, float frameDelay);

    /** \brief AnimationFrame Constructor
      * \param texCoord1 top-left texture coordinate to use
      * \param texCoord2 top-right texture coordinate to use
      * \param texCoord3 bottom-right texture coordinate to use
      * \param texCoord4 bottom-left texture coordinate to use
      * \param frameDelay Delay in milliseconds between this frame and the next
      */
    AnimationFrame(std::array<float, 2> texCoord1, std::array<float, 2> texCoord2, 
                   std::array<float, 2> texCoord3, std::array<float, 2> texCoord4,
                   float frameDelay);

    /// AnimationFrame Destructor
    ~AnimationFrame();

    /// \return Array representation of top-left coordinate in 2D-space where (x,y) = (0,1)
    const std::array<float, 2> getTexCoord1() const;

    /// \return Array representation of top-right coordinate in 2D-space where (x,y) = (0,1)
    const std::array<float, 2> getTexCoord2() const;

    /// \return Array representation of bottom-right coordinate in 2D-space where (x,y) = (0,1)
    const std::array<float, 2> getTexCoord3() const;

    /// \return Array representation of bottom-left coordinate in 2D-space where (x,y) = (0,1)
    const std::array<float, 2> getTexCoord4() const;

    /// \return Float representation of delay between this frame and the next in ms
    const float getFrameDelay() const;

protected:
    std::array<float, 2> mTexCoord1;  ///< top-left texture coordinate
    std::array<float, 2> mTexCoord2;  ///< top-right texture coordinate
    std::array<float, 2> mTexCoord3;  ///< bottom-right texture coordinate
    std::array<float, 2> mTexCoord4;  ///< bottom-left texture coordinate
    float                mFrameDelay; ///< Delay between this frame and the next in ms
};

#endif // _ANIMATIONFRAME_H
}}
