//#ifdef SFML
#include "../../graphics/Renderable.h"
#include "../../graphics/Renderer.h"
#include "../../utilities/Vertex2.h"
#include <SFML/Graphics.hpp>
#include <array>

namespace liquid { namespace impl {
#ifndef _SFMLRENDERABLE_H
#define _SFMLRENDERABLE_H

/**
 * \class SFMLRenderable
 * 
 * \ingroup Impl
 * \brief Implements graphics::Renderable for SFMLRenderable components
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 17/04/2017
 *
 */

class SFMLRenderable : public graphics::Renderable
{
public:
    /** \brief SFMLRenderable Constructor
      * \param vertices Array of Vertices that point to locations in space, used to define where/how Renderable is drawn
      * \param texture Texture to use for drawing this Renderable
      * \param layerDepth depth at which to draw this renderable
      */
    SFMLRenderable(std::array<utilities::Vertex2*, 4> vertices, sf::Texture& texture, float layerDepth);

    /// SFMLRenderable Destructor
    ~SFMLRenderable();

    /** \brief Override for drawing a single Renerable to the screen
      * \param renderer Pointer to the Renderer to use for drawing
      */
    virtual void draw(graphics::Renderer* renderer) override;

private:
    sf::Vertex convertFromVertex2(utilities::Vertex2* vert);

protected:
    const sf::Texture& mTexture; ///< Texture to use for drawing
};

#endif // _SFMLRENDERABLE_H
}}

//#endif // SFML
