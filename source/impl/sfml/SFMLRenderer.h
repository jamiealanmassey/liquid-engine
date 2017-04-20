#ifdef SFML
#include <SFML/Graphics.hpp>
#include "SFMLRenderable.h"
#include "../../data/Settings.h"
#include "../../graphics/Renderer.h"
#include "../../common/GameScene.h"

namespace liquid { namespace impl {
#ifndef _SFMLRENDERER_H
#define _SFMLRENDERER_H

/**
* \class SFMLRenderer
*
* \ingroup Impl
* \brief SFML specific implementation of the graphics::Renderer class
*
* \author Jamie Massey
* \version 1.0
* \date 17/04/2017
*
*/

class SFMLRenderable;
class SFMLRenderer : public graphics::Renderer
{
public:
    /** \brief SFMLRenderer Constructor
      * \param sceneParent Pointer the parent GameScene for this Renderer
      * \param setttings Optional paramater to extract settings for the sf::RenderWindow
      */
    SFMLRenderer(common::GameScene* sceneParent, data::Settings* settings = nullptr);

    /// SFMLRenderer Destructor
    ~SFMLRenderer();

    /// \brief Allows drawing to the sf::RenderWindow, call from GameScene
    virtual void draw() override;

    /// \return Pointer to the running sf::RenderWindow for this Renderer
    sf::RenderWindow* getRenderWindow() const;

protected:
    sf::RenderWindow* mRenderWindow; ///< Pointer to the stored sf::Renderwindow
};

#endif // _SFMLRENDERER_H
}}

#endif // SFML
