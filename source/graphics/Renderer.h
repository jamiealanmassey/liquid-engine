#include <array>
#include <map>
#include <list>
#include "../common/GameScene.h"
#include "../data/Settings.h"
#include "../graphics/LightingManager.h"
#include "IRenderable.h"

namespace liquid { namespace graphics {
#ifndef _RENDERER_H
#define _RENDERER_H

/**
 * \class Renderer
 *
 * \ingroup Graphics
 * \brief Interface class to define how to render the game world
 * 
 * \author Jamie Massey
 * \version 2.1
 * \date 16/04/2017
 * 
 */

class PostProcessor;
class Renderer
{
public:
    /** \brief Renderer Constructor
      * \param gameSceneParent Pointer to the parent common::GameScene
      */
    Renderer(data::Settings* settings = nullptr);

    /// Renderer Destructor
    ~Renderer();

    /** \brief Adds a Renderable to draw to the Renderer
      * \param renderable Interface class to add any Renderable type to the Renderer
      */
    virtual void addRenderable(IRenderable* renderable);
    
    /** \brief Remove a Renderable from the Renderer
      * \param renderable Pointer to the Renderable you want to remove
      */
    virtual void removeRenderable(IRenderable* renderable);

    /// \brief Called every frame to draw everything to the Screen
    virtual void draw(common::GameScene* gameScene);

    /** \brief Adds a PostProcessor effect to the Renderer
      * \param postProcessor Pointer to post processor to add
      */
    virtual void addPostProcessor(PostProcessor* postProcessor);

    /** \brief Remove a PostProcessor effect to the Renderer
      * \param postProcessor Pointer to post processor to add
      */
    virtual void removePostProcessor(PostProcessor* postProcessor);

    /** \brief Remove a PostProcessor effect to the Renderer
      * \param postProcessorName Name of PostProcessor to remove represented as an std::string
      */
    virtual void removePostProcessor(std::string postProcessorName);

    /// \brief Removes all attached PostProcessor objects
    virtual void removeAllPostProcessors();

    /// \return Gets the position of the mouse relative to the Renderer
    virtual std::array<float, 2> getMousePosition();

    void setLightingManager(graphics::LightingManager* lightingManager);

    /** \brief Get PostProcessor with the given name
      * \param postProcessorName std::string representation of the PostProcessor name
      * \return Pointer to the PostProcessor, nullptr if not found
      */
    PostProcessor* getPostProcessor(std::string postProcessorName);

    /** \brief Gets all the post processors
      * \return Collection of PostProcessors as a std::list
      */
    std::list<PostProcessor*>& getPostProcessors();

    /** \brief Gets all Renderable objects stored in the Renderer
      * \return Collection of Renderable objects as a std::list
      */
    std::list<IRenderable*>& getRenderables();

    graphics::LightingManager* getLightingManager();

protected:
    std::list<IRenderable*>    mRenderables;     ///< Collection of Renderable objects to be drawn every frame
    std::list<PostProcessor*>  mPostProcessors;  ///< Collection of PostProcessor objects to apply
    graphics::LightingManager* mLightingManager; ///< Pointer to the lighting::LightingManager
    data::Settings*            mSettings;        ///< Settings of the game
};

#endif // _RENDERER_H
}}
