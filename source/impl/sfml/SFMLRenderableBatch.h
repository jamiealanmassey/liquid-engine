#ifdef SFML
#include "../../graphics/RenderableBatch.h"
#include "../../graphics/Renderer.h"
#include <SFML/Graphics.hpp>

namespace liquid { namespace impl {
#ifndef _SFMLRENDERABLEBATCH_H
#define _SFMLRENDERABLEBATCH_H

/**
 * \class SFMLRenderableBatch
 *
 * \ingroup Impl
 * \brief SFML specific implementation for batch drawing objects to the screen, extends graphics::RenderableBatch
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 17/04/2017
 *
 */

class SFMLRenderableBatch : public graphics::RenderableBatch
{
public:
    /// SFMLRenderableBatch Constructor
    SFMLRenderableBatch(sf::Texture& texture, uint32_t defaultCapacity);

    /// SFMLRenderableBatch Destructor
    ~SFMLRenderableBatch();
    
    /** \brief Override draw for batch rendering given objects
      * \param renderer Pointer to Renderer to use for drawing
      */
    void draw(graphics::Renderer* renderer) override;

    /** \brief Override getting the next vertices of this batched Renderable
      * \return Array of generated vertices for drawing
      */
    std::array<utilities::Vertex2*, 4> nextVertices() override;

    /** \brief Sets the BlendMode of the whole SFMLRenderableBatch
      * \param mode Mode to set the BlendMode to
      */
    void setBlendMode(sf::BlendMode mode);

    /** \brief Sets the Shader of the whole SFMLRenderableBatch
      * \param shader Shader to bind to the SFMLRenderableBatch
      */
    void setShader(const sf::Shader shader);

    /// \return The size of the texture used in drawing
    sf::Vector2u getTextureSize() const;

private:
    void convertFromVertex2(int32_t index);

protected:
    const sf::Texture& mTexture;      ///< Texture to use for this SpriteBatch
    std::vector<sf::Vertex> mSFMLVertices; ///< SFML Vertices
    sf::RenderStates   mRenderStates; ///< RenderStates of the RenderableBatch
};

#endif // _SFMLRENDERABLEBATCH_H
}}

#endif // SFML
